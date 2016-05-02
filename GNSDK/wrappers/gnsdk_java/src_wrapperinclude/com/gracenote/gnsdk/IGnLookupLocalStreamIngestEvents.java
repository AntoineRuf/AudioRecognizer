package com.gracenote.gnsdk;

public interface IGnLookupLocalStreamIngestEvents {

	public void statusEvent(GnLookupLocalStreamIngestStatus status, String bundleId, IGnCancellable canceller);
	
}
