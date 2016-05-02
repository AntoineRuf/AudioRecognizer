package com.gracenote.gnsdk;

import java.nio.ByteBuffer;

import javax.sound.sampled.*;

/**
 * Uses Java audio system to retreive raw audio from the microphone. 
 * Warning! JVM support for microphones is spotty across operating systems, so the Java 
 * audio system, and therefore GnMic, are not a reliable ways to access the microphone in 
 * an application intended to support multiple platforms. Gracenote does not recommend
 * using this class in such applications.
 * If you have a custom solution for accessing the microphone, such as a custom native
 * library with JNI interface, you can create your own GnMic equivalent that can plug
 * directly in to GNSDK APIs. To do this simply have your microphone class implement 
 * the IGnAudioSource interface.
 */
public class GnMic implements IGnAudioSource {

	TargetDataLine 	microphone;
	
	public GnMic(){
		
	}

	/**
	 * Initializes the microphone by first checking if a microphone line is supported and
	 * if it is obtaining its target data line.
	 * @return Zero if successful, non-zero otherwise
	 */
	@Override
	public long sourceInit() {
		
		// check if microphone is supported at all
		if (AudioSystem.isLineSupported(Port.Info.MICROPHONE) == false) {
		    System.err.println("Microphone not supported");
		    return 1;
		}
		
		// find the mixer that has microphone, save its info
		Mixer.Info microphoneMixerInfo = null;
		Mixer.Info[] mixerInfos = AudioSystem.getMixerInfo();
		for (Mixer.Info info: mixerInfos){
			if ( AudioSystem.getMixer(info).isLineSupported(Port.Info.MICROPHONE) ) {
				microphoneMixerInfo = info;
				break;
			}
		}
		if ( microphoneMixerInfo == null ) {
			System.err.println("Microphone mixer not found");
			return 1;
		}
		
		AudioFormat format = new AudioFormat(8000.0f, 16, 1, true, true);
		try {
			microphone = AudioSystem.getTargetDataLine(format, microphoneMixerInfo);
			//microphone.addLineListener(new MicLineListener());
			microphone.open();
			microphone.start();
		} catch (LineUnavailableException e) {
			System.err.println("Error opening microphone mixer target data line: " + e.getMessage());
			e.printStackTrace();
			return 1;
		}
		
		return 0;
	}

	/**
	 * Closes the microphone target data line
	 */
	@Override
	public void sourceClose() {
		microphone.stop();
		microphone.close();
		microphone = null;
	}

	@Override
	public long samplesPerSecond() {
		return (long)microphone.getFormat().getSampleRate();
	}

	@Override
	public long sampleSizeInBits() {
		return (long)microphone.getFormat().getSampleSizeInBits();
	}

	@Override
	public long numberOfChannels() {
		return (long)microphone.getFormat().getChannels();
	}

	/**
	 * Reads data from the microphone target data line and copies it to the provided
	 * buffer
	 * @param dataBuffer	Buffer to copy raw audio data ti
	 * @param datSize		Size of dataBuffer
	 * @return Number of bytes copied in to dataBuffer
	 */
	@Override
	public long getData(ByteBuffer dataBuffer, long dataSize) {
		
		byte[] buffer = new byte[(int)dataSize];
		int bytesRead = 0;
		
		bytesRead = microphone.read(buffer, 0, (int)dataSize);
		
		dataBuffer.put(buffer);
		
		System.out.println("bytesRead = " + bytesRead);
		return bytesRead;
	}
	
	/*class MicLineListener implements LineListener {

		@Override
		public void update(LineEvent event) {
			LineEvent.Type type = event.getType();
			
			if ( type == LineEvent.Type.OPEN) {
				System.out.println("Line OPEN: " + event.getLine().getLineInfo().toString());
			} else if ( type == LineEvent.Type.CLOSE) {
				System.out.println("Line CLOSE: " + event.getLine().getLineInfo().toString());
			} else if ( type == LineEvent.Type.START) {
				System.out.println("Line START: " + event.getLine().getLineInfo().toString());
			} else if ( type == LineEvent.Type.STOP) {
				System.out.println("Line STOP: " + event.getLine().getLineInfo().toString());
			} else {
				System.out.println("Unknow event type");
			}
			
		}
	}*/
	
	/* On some OSes, like Mac, microphone is not supported. Run the code below to show
	   what can be accessed by thw Java sound system.
	   Code taken from http://stackoverflow.com/questions/562273/what-output-and-recording-ports-does-the-java-sound-api-find-on-your-computer
	void soundAudit() { 
		try {
		    System.out.println("OS: "+System.getProperty("os.name")+" "+
		      System.getProperty("os.version")+"/"+
		      System.getProperty("os.arch")+"\nJava: "+
		      System.getProperty("java.version")+" ("+
		      System.getProperty("java.vendor")+")\n");
		    
		    for (Mixer.Info thisMixerInfo : AudioSystem.getMixerInfo()) {
		    	
		    	System.out.println("Mixer: " + thisMixerInfo.getDescription() + " ["+thisMixerInfo.getName()+"]");
		    	Mixer thisMixer = AudioSystem.getMixer(thisMixerInfo);
		    	System.out.println("  Is Microphone Supported? " + thisMixer.isLineSupported(Port.Info.MICROPHONE));
		        for (Line.Info thisLineInfo:thisMixer.getSourceLineInfo()) {
		            
		        	if (thisLineInfo.getLineClass().getName().equals("javax.sound.sampled.Port")) {
		        		Line thisLine = thisMixer.getLine(thisLineInfo);
		        		thisLine.open();
		        		System.out.println("  Source Port: "+thisLineInfo.toString());
		              	for (Control thisControl : thisLine.getControls()) {
		              		System.out.println(AnalyzeControl(thisControl));
		              	}
		              	thisLine.close();
		        	}
		        }
		        
	        	for (Line.Info thisLineInfo:thisMixer.getTargetLineInfo()) {
	        		if (thisLineInfo.getLineClass().getName().equals("javax.sound.sampled.Port")) {
	        			Line thisLine = thisMixer.getLine(thisLineInfo);
	        			thisLine.open();
	        			System.out.println("  Target Port: "+thisLineInfo.toString());
	        			for (Control thisControl : thisLine.getControls()) {
	        				System.out.println(AnalyzeControl(thisControl));
	        			}
	        			thisLine.close();
	        		}
	        	}
		    }
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
		  
	public String AnalyzeControl(Control thisControl) {
		    
		String type = thisControl.getType().toString();
		if (thisControl instanceof BooleanControl) {
			return "    Control: "+type+" (boolean)"; 
		}
		
		if (thisControl instanceof CompoundControl) {	
			System.out.println("    Control: "+type+" (compound - values below)");
			String toReturn = "";
			for (Control children: ((CompoundControl)thisControl).getMemberControls()) {
				toReturn+="  "+AnalyzeControl(children)+"\n";
			}
			return toReturn.substring(0, toReturn.length()-1);
		}
		
		if (thisControl instanceof EnumControl) {
			return "    Control:"+type+" (enum: "+thisControl.toString()+")";
		}
		    
		if (thisControl instanceof FloatControl) {
			return "    Control: "+type+" (float: from "+
		        ((FloatControl) thisControl).getMinimum()+" to "+
		        ((FloatControl) thisControl).getMaximum()+")";
		}
		
		return "    Control: unknown type";
	}*/
	
}
