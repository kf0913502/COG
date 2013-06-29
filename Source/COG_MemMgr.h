#include <stdlib.h>

class MemMgr
{
	unsigned char ** m_ppMemBlocks; 
	unsigned char *	m_pHead;
	size_t m_ChunkSize;
	unsigned int m_NumChunks, m_nBlocks;
	bool m_Resizable;
	unsigned char * getNext(unsigned char * pItem);
	void setNext(unsigned char* pCurItem, unsigned char* pNextItem);
	
	void reset()
	{
		m_ppMemBlocks = NULL;
		m_pHead = NULL;
		m_ChunkSize = 0;
		m_NumChunks = 0;
		m_nBlocks = 0;
		m_Resizable = true;
	}
	unsigned char * createNewBlock();
	public:
		void init(unsigned int ChunkSize, unsigned int NumChunks);
		bool setResizable(bool Value){m_Resizable = Value;}
		MemMgr();
		~MemMgr();
		void destroy();
		bool growMemory();
		void * allocate();
		void free(void * pChunk);


};