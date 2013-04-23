#ifndef _AUDIO_OUTPUT_SOURCE_H_
#define _AUDIO_OUTPUT_SOURCE_H_
#include <binder/IPCThreadState.h>
#include <media/stagefright/AMRWriter.h>
#include <media/stagefright/CameraSource.h>
#include <media/stagefright/MPEG2TSWriter.h>
#include <media/stagefright/MPEG4Writer.h>
#include <media/stagefright/MediaDebug.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/OMXClient.h>
#include <media/stagefright/OMXCodec.h>
#include <media/MediaProfiles.h>
#include <camera/ICamera.h>
#include <camera/Camera.h>
#include <camera/CameraParameters.h>
#include <surfaceflinger/ISurface.h>
#include <utils/Errors.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <media/stagefright/AudioPlayer.h>
#include <media/stagefright/CameraSource.h>
#include <media/stagefright/FileSource.h>
#include <media/stagefright/MediaBufferGroup.h>
#include <media/stagefright/MediaDebug.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/MediaExtractor.h>
#include <media/stagefright/MPEG4Writer.h>
#include <media/stagefright/OMXClient.h>
#include <media/stagefright/OMXCodec.h>
#include <media/MediaPlayerInterface.h>

#include <sys/types.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <../../../../bionic/libc/include/fcntl.h>
#include <../../../../bionic/libc/kernel/common/linux/fb.h>
#include <linux/in.h>
#include <sys/un.h>
namespace android {
#define WIMO_FLAG
#ifdef	WIMO_FLAG
#define Audio_Data_Socket 1
#define Audio_Control_Socket 2
#define Audio_Client_Connect_Ok 2
#define Audio_Socket_Service_Magic 0xfa
#define MAX_Socket_Num 3
#define Audio_Socket_Service_CMD_BUTT 5
#define SUCCESS 0
#define FAILED -1
#define SHUT_DOWN_SOCKET(mSocket,Flag)  \
	shutdown(mSocket, Flag);\
	close(mSocket);\
	mSocket = -1;

typedef enum
{

    Audio_Control_Message                 = 0x0,
    Audio_Data_Message                 = 0x1,

}CLIENT_MSG_TYPE;
typedef enum
{

    Audio_Client_Connect                	= 0x0,
    Audio_Client_Connect_Ack_Ok		= 0x1,
    Audio_Client_Open_Req                	= 0x2,
    Audio_Client_Close_Req                 	= 0x3,

}CLIENT_CMD_TYPE;



typedef struct Socket_Msg
{
    uint8_t  magic;  //0xfa
    uint8_t  msg_type;
    uint8_t  cmd;    //control 0 open 1 close
    uint8_t  len;	
} Socket_Msg;

#endif
class Audio_OutPut_Source : public MediaSource {

public:
Audio_OutPut_Source(int32_t sampleRate, int32_t numChannels);

virtual ~Audio_OutPut_Source() ;

status_t start(MetaData *params) ;

status_t stop() ;
status_t connectt_to_server() ;
status_t disconnect() ;

sp<MetaData> getFormat() ;

status_t read(
        MediaBuffer **out, const ReadOptions *options) ;


    void* ThreadWrapper(void *);
	static void* rec_data(void* me);
	//status_t connect();

   


private:
    enum { kBufferSize = 2048 };
    static const double kFrequency = 500.0;
     long mOffset;
    long mLength;
    long head_offset;
    long tail_offset;
    long data_len;
    long file_offset;

    Mutex mLock;
    Condition DataRecCondition;
    int buf_size;
    uint8_t *rec_buf;

	
    int64_t *rec_buf_timestamp;
    int64_t last_alsa_time;
    int64_t last_enc_timestamp;
    int64_t start_data_time_us ;


 
    pthread_t mThread;
	
    bool mStarted;
    int32_t mSampleRate;
    int32_t mNumChannels;
    size_t mPhase;
	FILE* audio_input;
	FILE* audio_input_test;
    MediaBufferGroup mGroup;
uint8_t audio_input_buffer[8192];
uint8_t audio_temp_buffer[8192];
    int mSocket_Rec;
   
    int mSocket;
    struct pollfd fds;
    uint16_t   local_port;
    uint16_t   remote_port;
     struct sockaddr_un mUNIXAddr;	
    struct sockaddr_in mRTPAddr;
    struct sockaddr_un mRTP_REC_Addr;	
     int32_t is_last_has_data ;
     int rec_data_time ;
    int end_flag ;
    int do_end ;
	};
}
#endif
