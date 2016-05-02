package com.gracenote.gnsdk;

class IGnSystemEventsProxyU extends IGnSystemEventsProxyL {

	private IGnSystemEvents interfaceReference;

  	public IGnSystemEventsProxyU ( IGnSystemEvents interfaceReference ) {
	  	this.interfaceReference = interfaceReference;
    }
    
   	@Override
	public void localeUpdateNeeded(GnLocale locale) {
		if ( interfaceReference != null ) {
			interfaceReference.localeUpdateNeeded(locale);
		}
    }

	@Override
  	public void listUpdateNeeded(GnList list) {
		if ( interfaceReference != null ) {
			interfaceReference.listUpdateNeeded(list);
		}  	
    }

	@Override
  	public void systemMemoryWarning(long curMemSize, long memoryWarnSize) {
		if ( interfaceReference != null ) {
			interfaceReference.systemMemoryWarning(curMemSize, memoryWarnSize);
		}  	  	
    }

}
