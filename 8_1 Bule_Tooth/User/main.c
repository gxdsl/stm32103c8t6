#include "stm32f10x.h"
#include "valuepack.h"

// ������Ҫ�� �������ݰ� �� �������ݰ�  ���ݰ����в�ͬ���ͱ��������飬������valuepack.h�ж������ݰ��Ľṹ

TxPack txpack;
RxPack rxpack;

int main(void)
{

	// ��ʼ������ ���ò�����
  initValuePack(115200);
//  txpack.integers[0] = 1;

	while(1)
	{

		// ��ʱһ��ʱ��
		for(int i=0;i<100000;i++)
		{}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// �����շ�����
		
		if(readValuePack(&rxpack))
		{
//		
//			// �ڴ˶�ȡ�ֻ�����������
//			
//			// �����ǽ����յ�����ԭ���ش�
////			txpack.bools[0] = rxpack.bools[0];
////			txpack.bytes[0] = rxpack.bytes[0];
////			txpack.shorts[0] = rxpack.shorts[0];
			txpack.integers[0] = rxpack.integers[0];
////			txpack.floats[0] = rxpack.floats[0];

//			// ��Ҳ���԰� sendValuePack�����⣬������ֻ�е����յ��ֻ����������ݰ���Żش�����
			sendValuePack(&txpack);
		}

		// �ڴ˶����ݰ���ֵ�������ݷ��͵��ֻ�

//        sendValuePack(&txpack);

/// �����շ�����
///////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}
