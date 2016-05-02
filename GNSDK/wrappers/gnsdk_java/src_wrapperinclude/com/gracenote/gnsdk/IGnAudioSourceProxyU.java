package com.gracenote.gnsdk;

class IGnAudioSourceProxyU extends IGnAudioSourceProxyL {

	private IGnAudioSource interfaceReference;

  	public IGnAudioSourceProxyU( IGnAudioSource interfaceReference ) {
  		this.interfaceReference = interfaceReference;
  	}

	@Override
  	public long sourceInit() {
  		if ( interfaceReference != null ) {
  			return interfaceReference.sourceInit();
  		}
  		return 1;
  	}

	@Override
  	public void sourceClose() {
		if ( interfaceReference != null ) {
  			interfaceReference.sourceClose();
  		}  	
  	}

	@Override
  	public long samplesPerSecond() {
  		if ( interfaceReference != null ) {
  			return interfaceReference.samplesPerSecond();
  		}
  		return 0;  	
  	}

	@Override
  	public long sampleSizeInBits() {
  		if ( interfaceReference != null ) {
  			return interfaceReference.sampleSizeInBits();
  		}
  		return 0;   	
  	}

	@Override
  	public long numberOfChannels() {
  		if ( interfaceReference != null ) {
  			return interfaceReference.numberOfChannels();
  		}
  		return 0;   	
  	}

	@Override
  	public long getData(java.nio.ByteBuffer audioData, long dataSize) {
  		if ( interfaceReference != null ) {
  			return interfaceReference.getData(audioData, dataSize);
  		}
  		return 0;     	
  	}

}
