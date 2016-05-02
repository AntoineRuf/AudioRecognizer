package com.gracenote.gnsdk;

class IGnLogEventsProxyU extends IGnLogEventsProxyL {

	private IGnLogEvents interfaceReference; 

	public IGnLogEventsProxyU ( IGnLogEvents interfaceReference ) {
		this.interfaceReference = interfaceReference;
    }

	@Override
	public boolean logMessage(int packageId, GnLogMessageType messageType, long errorCode, String message) {
		if ( interfaceReference != null ) {
			return interfaceReference.logMessage( packageId, messageType, errorCode, message );
		}
		return false;
	}

}
