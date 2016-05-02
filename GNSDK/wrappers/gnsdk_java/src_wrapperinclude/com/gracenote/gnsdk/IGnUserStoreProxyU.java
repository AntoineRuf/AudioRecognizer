package com.gracenote.gnsdk;

class IGnUserStoreProxyU extends IGnUserStoreProxyL {

	private IGnUserStore interfaceReference;

	public IGnUserStoreProxyU( IGnUserStore interfaceReference ) {
		this.interfaceReference = interfaceReference;
  	}

  	public GnString LoadSerializedUser(String clientId) {
    	if ( interfaceReference != null ) {
    		return interfaceReference.loadSerializedUser( clientId );
    	}
    	return null;
  	}

  	public boolean StoreSerializedUser(String clientId, String userData) {
    	if ( interfaceReference != null ) {
    		return interfaceReference.storeSerializedUser( clientId, userData );
    	}
    	return false;
  	}

}
