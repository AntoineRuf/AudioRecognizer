
namespace GracenoteSDK {

using System;
using System.Runtime.InteropServices;

/**
* Delegate interface for retrieving audio data from an audio source such as a microphone, audio file
* or Internet stream.
* Various Gracenote methods consume audio data via audio sources, allowing the transfer
* of audio from the audio source to the consumer without requiring the application to
* manually pass the data. This can simplify the application's implementation.
* Applications are encouraged to implement their own audio source objects, or example if
* custom audio file format is used an application may implement an IGnAudioSource interface to
* the custom audio format decoder.
*/
public class IGnAudioSource : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IGnAudioSource(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(IGnAudioSource obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~IGnAudioSource() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          gnsdk_csharp_marshalPINVOKE.delete_IGnAudioSource(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

/**
* Initialize the audio source. This will be invoked prior to any other methods. If initialization
* fails return a non-zero value. In this case the consumer will not call any other methods
* including that to close the audio source.
* @return 0 indicates initialization was successful, non-zero otherwise.
*/
  public virtual uint SourceInit() {
    uint ret = gnsdk_csharp_marshalPINVOKE.IGnAudioSource_SourceInit(swigCPtr);
    return ret;
  }

/**
* Close the audio source. The consumer will not call any other methods after the source has
* been closed
*/
  public virtual void SourceClose() {
    gnsdk_csharp_marshalPINVOKE.IGnAudioSource_SourceClose(swigCPtr);
  }

/**
* Return the number of samples per second of the source audio format. Returns zero if called
* prior to SourceInit.
* @return Samples per second
*/
  public virtual uint SamplesPerSecond() {
    uint ret = gnsdk_csharp_marshalPINVOKE.IGnAudioSource_SamplesPerSecond(swigCPtr);
    return ret;
  }

/**
* Return the number of bits in a sample of the source audio format. Returns zero if called
* prior to SourceInit.
* @return Sample size in bits
*/
  public virtual uint SampleSizeInBits() {
    uint ret = gnsdk_csharp_marshalPINVOKE.IGnAudioSource_SampleSizeInBits(swigCPtr);
    return ret;
  }

/**
* Return the number of channels of the source audio format. Returns zero if called
* prior to SourceInit.
* @return Number of channels
*/
  public virtual uint NumberOfChannels() {
    uint ret = gnsdk_csharp_marshalPINVOKE.IGnAudioSource_NumberOfChannels(swigCPtr);
    return ret;
  }

/**
* Get audio data from the audio source. This is a blocking call meaning it should
* not return until there is data available.
* When data is available this method must
* copy data to the provided buffer ensuring not to overflow it. The number of bytes
* copied to the buffer is returned.
* To signal the audio source is unable to deliver anymore data return zero. The
* consumer will then stop requesting data and close the audio source.
* @param dataBuffer 	[out] Buffer to receive audio data
* @param dataSize 		[in]  Size in bytes of buffer
* @return Number of bytes copied to the buffer. Return zero to indicate
* 		   no more data can be delivered via the audio source.
*/
  public virtual uint GetData(byte[] dataBuffer, uint dataSize) {
    uint ret = gnsdk_csharp_marshalPINVOKE.IGnAudioSource_GetData(swigCPtr, dataBuffer, dataSize);
    return ret;
  }

  public IGnAudioSource() : this(gnsdk_csharp_marshalPINVOKE.new_IGnAudioSource(), true) {
    SwigDirectorConnect();
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("SourceInit", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateIGnAudioSource_0(SwigDirectorSourceInit);
    if (SwigDerivedClassHasMethod("SourceClose", swigMethodTypes1))
      swigDelegate1 = new SwigDelegateIGnAudioSource_1(SwigDirectorSourceClose);
    if (SwigDerivedClassHasMethod("SamplesPerSecond", swigMethodTypes2))
      swigDelegate2 = new SwigDelegateIGnAudioSource_2(SwigDirectorSamplesPerSecond);
    if (SwigDerivedClassHasMethod("SampleSizeInBits", swigMethodTypes3))
      swigDelegate3 = new SwigDelegateIGnAudioSource_3(SwigDirectorSampleSizeInBits);
    if (SwigDerivedClassHasMethod("NumberOfChannels", swigMethodTypes4))
      swigDelegate4 = new SwigDelegateIGnAudioSource_4(SwigDirectorNumberOfChannels);
    if (SwigDerivedClassHasMethod("GetData", swigMethodTypes5))
      swigDelegate5 = new SwigDelegateIGnAudioSource_5(SwigDirectorGetData);
    gnsdk_csharp_marshalPINVOKE.IGnAudioSource_director_connect(swigCPtr, swigDelegate0, swigDelegate1, swigDelegate2, swigDelegate3, swigDelegate4, swigDelegate5);
  }

  private bool SwigDerivedClassHasMethod(string methodName, Type[] methodTypes) {
    System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(IGnAudioSource));
    return hasDerivedMethod;
  }

  private uint SwigDirectorSourceInit() {
    return SourceInit();
  }

  private void SwigDirectorSourceClose() {
    SourceClose();
  }

  private uint SwigDirectorSamplesPerSecond() {
    return SamplesPerSecond();
  }

  private uint SwigDirectorSampleSizeInBits() {
    return SampleSizeInBits();
  }

  private uint SwigDirectorNumberOfChannels() {
    return NumberOfChannels();
  }

  private uint SwigDirectorGetData(byte[] dataBuffer, uint dataSize) {
 byte[] tempdataBuffer = dataBuffer;
    try {
      return GetData(tempdataBuffer, dataSize);
    } finally {
 
    }
  }

  public delegate uint SwigDelegateIGnAudioSource_0();
  public delegate void SwigDelegateIGnAudioSource_1();
  public delegate uint SwigDelegateIGnAudioSource_2();
  public delegate uint SwigDelegateIGnAudioSource_3();
  public delegate uint SwigDelegateIGnAudioSource_4();
  public delegate uint SwigDelegateIGnAudioSource_5(byte[] dataBuffer, uint dataSize);

  private SwigDelegateIGnAudioSource_0 swigDelegate0;
  private SwigDelegateIGnAudioSource_1 swigDelegate1;
  private SwigDelegateIGnAudioSource_2 swigDelegate2;
  private SwigDelegateIGnAudioSource_3 swigDelegate3;
  private SwigDelegateIGnAudioSource_4 swigDelegate4;
  private SwigDelegateIGnAudioSource_5 swigDelegate5;

  private static Type[] swigMethodTypes0 = new Type[] {  };
  private static Type[] swigMethodTypes1 = new Type[] {  };
  private static Type[] swigMethodTypes2 = new Type[] {  };
  private static Type[] swigMethodTypes3 = new Type[] {  };
  private static Type[] swigMethodTypes4 = new Type[] {  };
  private static Type[] swigMethodTypes5 = new Type[] { typeof(byte[]), typeof(uint) };
}

}
