package com.gracenote.gnsdk;

class IGnStatusEventsProxyU extends IGnStatusEventsProxyL {

	private IGnStatusEvents interfaceReference;

	IGnStatusEventsProxyU (IGnStatusEvents interfaceReference) {
		this.interfaceReference = interfaceReference;
	}
	
	@Override	
	public void statusEvent(GnStatus status, long percentComplete, long bytesTotalSent, long bytesTotalReceived, IGnCancellable canceller) {
		if ( interfaceReference != null ) {
			interfaceReference.statusEvent(status, percentComplete, bytesTotalSent, bytesTotalReceived, canceller);
		}
	}
	
}

