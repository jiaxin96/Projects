package ImageDeal;

import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.FilteredImageSource;
import java.awt.image.RGBImageFilter;

import imagereader.IImageProcessor;

public class ImplementImageProcessor implements IImageProcessor {


	//蓝色
	private class BlueFilter extends RGBImageFilter {
		@Override
		public int filterRGB(int x, int y, int rgb) {
			return rgb & 0xff0000ff;
		}
	}
	// 绿色
	private class GreenFilter extends RGBImageFilter {
		@Override
		public int filterRGB(int x, int y, int rgb) {
			return rgb & 0xff00ff00;
		}
	}
	// 红色
	private class RedFilter extends RGBImageFilter {
		@Override
		public int filterRGB(int x, int y, int rgb) {
			return rgb & 0xffff0000;
		}
	}
	// 黑白
	private class GreyFilter extends RGBImageFilter {
		@Override
		public int filterRGB(int x, int y, int rgb) {
			int grey = (int) ( (((rgb & 0x00ff0000) >> 16)*0.299) + (((rgb & 0x0000ff00) >> 8)*0.587) + (((rgb & 0x000000ff))*0.114));
			// 0xffgygygy
			return (255<<24) +( grey << 16) + (grey << 8) + grey;
		}
	}
	
	@Override
	public Image showChanelB(Image img) {
		BlueFilter blueFilter = new BlueFilter();
		return Toolkit.getDefaultToolkit().createImage(new FilteredImageSource(img.getSource(), blueFilter));
	}

	@Override
	public Image showChanelG(Image img) {
		GreenFilter greenFilter = new GreenFilter();
		return Toolkit.getDefaultToolkit().createImage(new FilteredImageSource(img.getSource(), greenFilter));
	}

	@Override
	public Image showChanelR(Image img) {
		RedFilter redFilter = new RedFilter();
		return Toolkit.getDefaultToolkit().createImage(new FilteredImageSource(img.getSource(), redFilter));
	}

	@Override
	public Image showGray(Image img) {
		GreyFilter greyFilter = new GreyFilter();
		return Toolkit.getDefaultToolkit().createImage(new FilteredImageSource(img.getSource(), greyFilter));
	}


}
