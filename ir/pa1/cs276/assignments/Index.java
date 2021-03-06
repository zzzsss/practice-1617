package cs276.assignments;

import cs276.util.Pair;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.util.*;

public class Index {

	// Term id -> (position in index file, doc frequency) dictionary
	private static Map<Integer, Pair<Long, Integer>> postingDict 
		= new TreeMap<Integer, Pair<Long, Integer>>();
	// Doc name -> doc id dictionary
	private static Map<String, Integer> docDict
		= new TreeMap<String, Integer>();
	// Term -> term id dictionary
	private static Map<String, Integer> termDict
		= new TreeMap<String, Integer>();
	// Block queue
	private static LinkedList<File> blockQueue
		= new LinkedList<File>();

	// Total file counter
	private static int totalFileCount = 0;
	// Document counter
	private static int docIdCounter = 0;
	// Term counter
	private static int wordIdCounter = 0;
	// Index
	private static BaseIndex index = null;

	
	/* 
	 * Write a posting list to the given file 
	 * You should record the file position of this posting list
	 * so that you can read it back during retrieval
	 * 
	 * */
	private static void writePosting(FileChannel fc, PostingList posting)
			throws IOException {
		/*
		 * zTODO: Your code here
		 *	 
		 */
        postingDict.put(posting.getTermId(), new Pair<>(fc.position(), posting.getList().size()));
        index.writePosting(fc, posting);
	}

	public static void main(String[] args) throws IOException {
		/* Parse command line */
		if (args.length != 3) {
			System.err.println("Usage: java Index [Basic|VB|Gamma] data_dir output_dir");
			return;
		}

		/* Get index */
		String className = "cs276.assignments." + args[0] + "Index";
		try {
			Class<?> indexClass = Class.forName(className);
			index = (BaseIndex) indexClass.newInstance();
		} catch (Exception e) {
			System.err
					.println("Index method must be \"Basic\", \"VB\", or \"Gamma\"");
			throw new RuntimeException(e);
		}

		/* Get root directory */
		String root = args[1];
		File rootdir = new File(root);
		if (!rootdir.exists() || !rootdir.isDirectory()) {
			System.err.println("Invalid data directory: " + root);
			return;
		}

		/* Get output directory */
		String output = args[2];
		File outdir = new File(output);
		if (outdir.exists() && !outdir.isDirectory()) {
			System.err.println("Invalid output directory: " + output);
			return;
		}

		if (!outdir.exists()) {
			if (!outdir.mkdirs()) {
				System.err.println("Create output directory failure");
				return;
			}
		}

		/* BSBI indexing algorithm */
		File[] dirlist = rootdir.listFiles();

		/* For each block */
		for (File block : dirlist) {
            // the <termID, docID> pair
            List<Pair<Integer, Integer>> id_pairs = new ArrayList<>();

			File blockFile = new File(output, block.getName());
			blockQueue.add(blockFile);

			File blockDir = new File(root, block.getName());
			File[] filelist = blockDir.listFiles();
			
			/* For each file */
			for (File file : filelist) {
				++totalFileCount;
				String fileName = block.getName() + "/" + file.getName();
				docDict.put(fileName, docIdCounter++);
				
				BufferedReader reader = new BufferedReader(new FileReader(file));
				String line;
				while ((line = reader.readLine()) != null) {
					String[] tokens = line.trim().split("\\s+");
					for (String token : tokens) {
						/*
						 * zTODO: Your code here
						 *       For each term, build up a list of
						 *       documents in which the term occurs
						 */
						if(!termDict.containsKey(token))    // put into dictionary
                            termDict.put(token, wordIdCounter++);
                        id_pairs.add(new Pair<>(termDict.get(token), docIdCounter-1));
					}
				}
				reader.close();
			}

			/* Sort and output */
			if (!blockFile.createNewFile()) {
				System.err.println("Create new block failure.");
				return;
			}
			
			RandomAccessFile bfc = new RandomAccessFile(blockFile, "rw");
			
			/*
			 * zTODO: Your code here
			 *       Write all posting lists for all terms to file (bfc) 
			 */
            // sort by termID/DocID
            id_pairs.sort(new Comparator<Pair<Integer, Integer>>(){
                public int compare(Pair<Integer, Integer> arg0, Pair<Integer, Integer> arg1) {
                    if(arg0.getFirst() < arg1.getFirst())
                        return -1;
                    else if(arg0.getFirst().equals(arg1.getFirst()) && arg0.getSecond() < arg1.getSecond())
                        return -1;
					else if(arg0.getFirst().equals(arg1.getFirst()) && arg0.getSecond().equals(arg1.getSecond()))
						return 0;
                    else
                        return 1;
                }
            });
            // write to file
            FileChannel bfc_channel = bfc.getChannel();
            Integer term_previous = -1;
            List<Integer> postings = new ArrayList<>();
            for(Pair<Integer, Integer> one: id_pairs){
                Integer tid = one.getFirst();
                Integer did = one.getSecond();
                if(!tid.equals(term_previous)){
                    if(!postings.isEmpty())
                        writePosting(bfc_channel, new PostingList(term_previous, postings));
                    term_previous = tid;
                    postings = new ArrayList<>();
                    postings.add(did);
                }
                else if(!did.equals(postings.get(postings.size()-1)))
                    postings.add(did);
            }
            if(!postings.isEmpty())
                writePosting(bfc_channel, new PostingList(term_previous, postings));
            bfc_channel.close();
		}

		/* Required: output total number of files. */
		System.out.println(totalFileCount);

		/* Merge blocks */
		while (true) {
			if (blockQueue.size() <= 1)
				break;

			File b1 = blockQueue.removeFirst();
			File b2 = blockQueue.removeFirst();
			
			File combfile = new File(output, b1.getName() + "+" + b2.getName());
			if (!combfile.createNewFile()) {
				System.err.println("Create new block failure.");
				return;
			}

			RandomAccessFile bf1 = new RandomAccessFile(b1, "r");
			RandomAccessFile bf2 = new RandomAccessFile(b2, "r");
			RandomAccessFile mf = new RandomAccessFile(combfile, "rw");
			 
			/*
			 * zTODO: Your code here
			 *       Combine blocks bf1 and bf2 into our combined file, mf
			 *       You will want to consider in what order to merge
			 *       the two blocks (based on term ID, perhaps?).
			 *       
			 */
            FileChannel bf1_channel = bf1.getChannel();
            FileChannel bf2_channel = bf2.getChannel();
            FileChannel m_channel = mf.getChannel();
            PostingList p1 = index.readPosting(bf1_channel);
            PostingList p2 = index.readPosting(bf2_channel);
            while(p1!=null && p2!=null){
                if(p1.getTermId() < p2.getTermId()) {
                    writePosting(m_channel, p1);
                    p1 = index.readPosting(bf1_channel);
                }
                else if(p1.getTermId() > p2.getTermId()) {
                    writePosting(m_channel, p2);
                    p2 = index.readPosting(bf2_channel);
                }
                else{
                    List<Integer> p1l = p1.getList();
                    List<Integer> p2l = p2.getList();
					p1l.addAll(p2l);
                    Collections.sort(p1l);  // this is waste of time
					writePosting(m_channel, new PostingList(p1.getTermId(), p1l));
                    p1 = index.readPosting(bf1_channel);
                    p2 = index.readPosting(bf2_channel);
                }
            }
            while(p1!=null) {
                writePosting(m_channel, p1);
                p1 = index.readPosting(bf1_channel);
            }
            while(p2!=null) {
                writePosting(m_channel, p2);
                p2 = index.readPosting(bf2_channel);
            }

            bf1_channel.close();
            bf2_channel.close();
            m_channel.close();
			b1.delete();
			b2.delete();
			blockQueue.add(combfile);
		}

		/* Dump constructed index back into file system */
		File indexFile = blockQueue.removeFirst();
		indexFile.renameTo(new File(output, "corpus.index"));

		BufferedWriter termWriter = new BufferedWriter(new FileWriter(new File(
				output, "term.dict")));
		for (String term : termDict.keySet()) {
			termWriter.write(term + "\t" + termDict.get(term) + "\n");
		}
		termWriter.close();

		BufferedWriter docWriter = new BufferedWriter(new FileWriter(new File(
				output, "doc.dict")));
		for (String doc : docDict.keySet()) {
			docWriter.write(doc + "\t" + docDict.get(doc) + "\n");
		}
		docWriter.close();

		BufferedWriter postWriter = new BufferedWriter(new FileWriter(new File(
				output, "posting.dict")));
		for (Integer termId : postingDict.keySet()) {
			postWriter.write(termId + "\t" + postingDict.get(termId).getFirst()
					+ "\t" + postingDict.get(termId).getSecond() + "\n");
		}
		postWriter.close();
	}

}
