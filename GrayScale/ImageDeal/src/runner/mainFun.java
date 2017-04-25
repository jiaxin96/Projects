package runner;

import ImageDeal.ImplementImageIO;
import ImageDeal.ImplementImageProcessor;
import imagereader.Runner;

public class mainFun {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ImplementImageIO imageioer = new ImplementImageIO();
		ImplementImageProcessor processor = new ImplementImageProcessor();
        Runner.run(imageioer, processor);
	}
}