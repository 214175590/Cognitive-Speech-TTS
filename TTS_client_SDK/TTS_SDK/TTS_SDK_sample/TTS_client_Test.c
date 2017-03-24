#include<stdio.h>
#include"iconv\iconv.h"
#include"TTS_SDK.h"
#include<time.h>
#include<windows.h>
#include"azure_c_shared_utility\httpapi.h"
#include"azure_c_shared_utility\audio_sys.h"

const unsigned char* ApiKey = "f2c0453f2e0e448584f76e3d25989df1";

const char* text = "����˵���������ź�����û�г���һ����Ů����\
΢��Ů����������������һ��΢�ֵ�Ů�������ϳ��ŵ��ȸ��ɷ�ǿɰ���ͷ���������̣�������������β�Ժ��Ҿͳ��˰��Ͻ����һö�̷�Ů����\
�����������Լ��ķ��ͣ��������߷֣���ס�����˾ͼ��������ͷ�����úܵͣ���Ϊͷ���ж̵�Ե�ʣ��ҴӺ��濴���������ĸ��Ƕȶ��������ķ�����������衣\
��˵��ϲ�������������񺫾���Ů���ǵ�ƮƮ�������������������ӣ�����һ�ֲ�������������������������������Ƶ��ǳ����񣬻�����һ���������˵�ģ����\
ֻ�ǣ��������е�������δ��������Щ��ǳ�˰ɣ�����ͷ��������������������ֻ��˵����ֻ������ǰ�������֡�\
��������ٲ�����ɫ�����ڶ����ķ��룬�������ǻ�Ϊ�Լ�����ò�е��������������Ա�����ż���ᷢ����ɧ˵�Լ��ְ������ֳ�\
���ʱ���һ���������ͷ���������������䲻�������˶��������ǵľ�ɫ���ˣ������˳��úÿ������˳��ò���ô�ÿ��������ϵ��ڹ���һ����ʱҲ������ش�һ�ȴ�����\
��˵��ϲ�������������񺫾���Ů���ǵ�ƮƮ�������������������ӣ�����һ�ֲ�������������������������������Ƶ��ǳ�����\
������һ���������˵�ģ����ֻ�ǣ��������е�������δ��������Щ��ǳ�˰ɣ�����ͷ��������������������ֻ��˵����ֻ������ǰ�������֡�\
��������ٲ�����ɫ�����ڶ����ķ��룬�������ǻ�Ϊ�Լ�����ò�е��������������Ա�����ż���ᷢ����ɧ˵�Լ��ְ������ֳ�\
���ʱ���һ���������ͷ���������������䲻�������˶��������ǵľ�ɫ���ˣ������˳��úÿ������˳��ò���ô�ÿ��������ϵ��ڹ���һ����ʱҲ������ش�һ�ȴ�����\
��ʵ˵����Ҳ��֪���Լ�������߶߶Щʲô���������������ᶮ�ġ����ԣ���ʹ�೤�ڿ����ǵİ�װֽ��д�ˡ��������ôԽ��Խ���ˡ�\
������������Ь�������ĳ嶯�Ļ��ݸ���ʱ���ֹۻ��İ������ǻ�΢Ц���ڱ���д�ϡ�����ô˵������ǰ�Һ���ඡ���Ȼ��ݸ�Ƿ��İ೤��";

int conversion(const unsigned char* inbuf, unsigned char* outbuf, size_t outlen, const char* tocode, const char* fromcode) {
	int inlen = strlen(inbuf);
	iconv_t cd = iconv_open(tocode, fromcode);
	char *tmpOutbuf = (char *)malloc(inlen * 4);
	memset(tmpOutbuf, 0, inlen * 4);
	char *in = inbuf;
	char *out = tmpOutbuf;
	size_t tmpOutlen = inlen * 4;
	iconv(cd, &in, (size_t *)&inlen, &out, &tmpOutlen);
	tmpOutlen = strlen(tmpOutbuf);

	if (tmpOutlen >= outlen) {
		free(tmpOutbuf);
		iconv_close(cd);
		return -1;
	}
	else {
		strcpy(outbuf, tmpOutbuf);
		free(tmpOutbuf);
		iconv_close(cd);
		return 0;
	}
}

void main() {

	MSTTS_RESULT result;
	MSTTSHANDLE MSTTShandle;
	
	result = MSTTS_CreateSpeechSynthesizerHandler(&MSTTShandle, ApiKey);

	//MSTTS_RESULT MSTTS_SetVoice(MSTTSHANDLE hSynthesizerHandle, const MSTTSVoiceInfo* pVoiceInfo);

	unsigned char* bodyText = malloc(10000);
	if (bodyText == NULL) {
		printf("malloc failed");
		return;
	}
	memset(bodyText, 0, 10000);
	conversion(text, bodyText, 10000, "utf-8", "GBK");

	result = MSTTS_Speak(MSTTShandle, bodyText, MSTTSContentType_PlainText);

	MSTTS_CloseSynthesizer(MSTTShandle);

	free(bodyText);

	getch();
}
