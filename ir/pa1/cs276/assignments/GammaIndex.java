package cs276.assignments;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.*;

public class GammaIndex implements BaseIndex {
	// for this one, int should be <= 31 bits; each PostingList does not share byte
    // ---- write ----
    static byte[] l2bs(List<Boolean> l){
        // 0/1 list
        byte[] ret = new byte[(l.size()+7)/8];
        for(int i=0; i<ret.length; i++){
            ret[i] = 0;
            for(int j=0; j<8; j++) {
                int index = i*8+j;
                if(index < l.size() && l.get(index))
                    ret[i] |= (byte) (1 << (7 - j));
            }
        }
        return ret;
    }
    static List<Boolean> i2l(int x){
        x += 1; // 0 as 1, ...
        List<Boolean> ret = new ArrayList<>();
        List<Boolean> fields = new ArrayList<>();
        while(x != 0){
            if((x & 0x1) != 0)
                fields.add(true);
            else
                fields.add(false);
            x = (x>>1);
        }
        fields.remove(fields.size()-1); // remove last one
        Collections.reverse(fields);    // BIG-END
        for(int i=0; i<fields.size(); i++)
            ret.add(true);  // 1
        ret.add(false);     // 0
        ret.addAll(fields);
        return ret;
    }
    // ---- read ----
    static void read_byte(FileChannel fc, Queue<Boolean> q) throws IOException{
        ByteBuffer x = ByteBuffer.allocate(1);
        fc.read(x);
        x.flip();
        byte one = x.get();
        for(int i=0; i<8; i++)
            q.add(((one & (1<<(7-i)))!=0));
    }
    static int read_one(FileChannel fc, Queue<Boolean> q) throws IOException{
        // read one int, also fill q if necessary
        int ret = 1;    // start with discarded msb 1
        // 1. length
        int length = 0;
        while(true){
            if(q.isEmpty())
                read_byte(fc, q);   // load more bits
            Boolean n = q.poll();
            if(n)
                length++;
            else    // zero
                break;
        }
        // 2. fields
        for(int i=0; i<length; i++){
            if(q.isEmpty())
                read_byte(fc, q);   // load more bits
            Boolean n = q.poll();
            ret = ret*2 + (n ? 1 : 0);  // BIG-END
        }
        return ret-1;
    }

	@Override
	public PostingList readPosting(FileChannel fc) {
		/*
		 * zTODO: Your code here
		 */
        int term = 0;
        List<Integer> posts = new ArrayList<>();
        try {
            if(fc.position() == fc.size())
                return null;
            // zTODO
            Queue<Boolean> q = new LinkedList<>();
            term = read_one(fc, q);
            int length = read_one(fc, q);
            int current = 0;
            for(int i=0; i<length; i++) {
                posts.add(current + read_one(fc, q));
                current = posts.get(posts.size()-1);
            }
        }
        catch (IOException x){
            System.err.println(x.getMessage());
        }
        return new PostingList(term, posts);
	}

	@Override
	public void writePosting(FileChannel fc, PostingList p) {
		/*
		 * zTODO: Your code here
		 */
        List<Boolean> to_put = new ArrayList<>();
        to_put.addAll(i2l(p.getTermId()));
        to_put.addAll(i2l(p.getList().size()));
        int current = 0;
        for(int x: p.getList()) {
            to_put.addAll(i2l(x-current));
            current = x;
        }
        try {
            fc.write(ByteBuffer.wrap(l2bs(to_put)));
        }
        catch (IOException x){
            System.err.println(x.getMessage());
        }
	}
}
