package cs276.assignments;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.*;

public class VBIndex implements BaseIndex {

    // these two never check fc
    private byte[] get_numberstream(Integer n){ // Big-end
        ArrayList<Byte> l = new ArrayList<>();
        while(true){
            Byte x = (byte)(n%128);
            l.add(x);
            n = n/128;
            if(n == 0)
                break;
        }
        Collections.reverse(l);
        byte[] to_put = new byte[l.size()];
        for(int i=0;i<l.size();i++)
            to_put[i] = l.get(i);
        to_put[l.size()-1] |= 0x80;
        return to_put;
    }
    private void put_number(FileChannel fc, Integer n) throws IOException{
        fc.write(ByteBuffer.wrap(get_numberstream(n)));
    }
    private int get_number(FileChannel fc) throws IOException{
        int ret = 0;
        while(true) {
            ByteBuffer x = ByteBuffer.allocate(1);
            fc.read(x);
            x.flip();
            byte one = x.get();
            if (one < 0) {
                ret = ret * 128 + (one & 0x7f);
                break;
            } else
                ret = ret * 128 + one;
        }
        return ret;
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
            term = get_number(fc);
            int length = get_number(fc);
            //System.out.print("Read one: "+term+"/"+length+"\n");
            int previous = 0;
            for(int i=0;i<length;i++){
                previous += get_number(fc);
                posts.add(previous);
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
		try {
            // write [id, num, ...]
            put_number(fc, p.getTermId());
            put_number(fc, p.getList().size());
            int previous = 0;
            for(Integer n: p.getList()) {
                put_number(fc, n-previous);
                previous = n;
            }
        }
		catch (IOException x){
			System.err.println(x.getMessage());
		}
	}

    public static void main(String[] arg){
        VBIndex t = new VBIndex();
        byte[] x = t.get_numberstream(0xff);
        x[x.length-1] &= 0x7f;
        System.out.println(x);
    }
}
