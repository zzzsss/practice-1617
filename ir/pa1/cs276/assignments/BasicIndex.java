package cs276.assignments;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.*;

public class BasicIndex implements BaseIndex {

	@Override
	public PostingList readPosting(FileChannel fc) {
		/*
		 * zTODO: Your code here
		 *       Read and return the postings list from the given file.
		 */
        int term = 0;
        List<Integer> posts = new ArrayList<>();
        try {
            if(fc.position() == fc.size())
                return null;
            ByteBuffer x = ByteBuffer.allocate(4);
            fc.read(x);
            x.flip(); term = x.getInt(); x.clear();
            fc.read(x);
            x.flip(); int s = x.getInt(); x.clear();
            for(int i=0;i<s;i++){
                fc.read(x);
                x.flip(); posts.add(x.getInt()); x.clear();
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
		 *       Write the given postings list to the given file.
		 */
        try {
            ByteBuffer x = ByteBuffer.allocate(4);
            x.clear(); x.putInt(p.getTermId()); x.flip();
            fc.write(x);
            x.clear(); x.putInt(p.getList().size()); x.flip();
            fc.write(x);
            for (int e : p.getList()) {
                x.clear(); x.putInt(e); x.flip();
                fc.write(x);
            }
        }
        catch (IOException x){
            System.err.println(x.getMessage());
        }
	}

    static public void main(String args[]) throws Exception{
        RandomAccessFile f = new RandomAccessFile("test", "rw");
        FileChannel fc = f.getChannel();
        ByteBuffer x = ByteBuffer.allocate(4);
        x.putInt(100);
        x.flip();
        fc.write(x);
        fc.force(false);
        fc.close();
    }
}
