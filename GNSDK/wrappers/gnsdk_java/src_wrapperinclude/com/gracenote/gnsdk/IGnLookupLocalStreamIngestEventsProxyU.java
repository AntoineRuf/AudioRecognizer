package com.gracenote.gnsdk;

public class IGnLookupLocalStreamIngestEventsProxyU extends IGnLookupLocalStreamIngestEventsProxyL {

	private IGnLookupLocalStreamIngestEvents interfaceReference;

	IGnLookupLocalStreamIngestEventsProxyU (IGnLookupLocalStreamIngestEvents interfaceReference) {
		this.interfaceReference = interfaceReference;
	}
	
	@Override
	public void statusEvent(GnLookupLocalStreamIngestStatus status, String bundleId, IGnCancellable canceller) {
		if ( interfaceReference != null ) {
			interfaceReference.statusEvent( status, bundleId, canceller );
		}
	}
	
}
