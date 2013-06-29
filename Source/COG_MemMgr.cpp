#include "COG_MemMgr.h"
#include <iostream>



MemMgr::MemMgr()
{
	reset();
}

void MemMgr::init(unsigned int ChunkSize, unsigned int NumChunks)
{

	m_ChunkSize = ChunkSize;
	m_NumChunks = NumChunks;

	growMemory();
}
unsigned char * MemMgr::createNewBlock()
{


	size_t BlockSize = m_ChunkSize + sizeof(unsigned char *);
	size_t TrueSize = BlockSize*m_NumChunks;
	unsigned char * pCur = (unsigned char *)malloc(TrueSize);
	if (!pCur) return NULL;
	unsigned char *pEnd = pCur + TrueSize;
	unsigned char * pFirst = pCur;
	while(pCur < pEnd)
		{
			unsigned char * pNext = pCur + BlockSize;
			unsigned char ** ppChunkHeader = (unsigned char **)pCur;
			*ppChunkHeader = (pNext < pEnd ? pNext : NULL);
			pCur = pNext;
		}

	return pFirst;
}

bool MemMgr::growMemory()
{
	m_nBlocks++;
	unsigned char ** ppOldMemBlocks = m_ppMemBlocks;
	m_ppMemBlocks = (unsigned char **)malloc(m_nBlocks*sizeof(unsigned char *));

	if(!m_ppMemBlocks) return false;

	for(int i=0; i<m_nBlocks-1; i++) m_ppMemBlocks[i] = ppOldMemBlocks[i];
	m_ppMemBlocks[m_nBlocks-1] = createNewBlock();

	if (m_pHead)
	{
		unsigned char * pCur = (unsigned char*)m_pHead;
		unsigned char * pNext = getNext(pCur);

		while(pNext)
		{
			pCur = pNext;
			pNext = getNext(pCur);
		}

		setNext(pNext, m_ppMemBlocks[m_nBlocks-1]);
	}
	else
	{
		m_pHead = m_ppMemBlocks[m_nBlocks-1];
	}

	std::free(ppOldMemBlocks);
}


 unsigned char * MemMgr::getNext(unsigned char * pItem)
{
	return *(unsigned char **)pItem;
}


void MemMgr::setNext(unsigned char* pCurItem, unsigned char* pNextItem)
{
	*(unsigned char **)pCurItem = pNextItem;
}

void * MemMgr::allocate()
{
	if (! m_pHead)
	{
		if (!m_Resizable) return NULL;

		if (!growMemory()) return NULL;



	}
	unsigned char * CurHead = m_pHead;
	m_pHead = getNext(m_pHead);
	return CurHead + sizeof(unsigned char *);
}

void MemMgr::free(void * pChunk)
{

	unsigned char * pChunkHeader = (unsigned char *)pChunk - sizeof(unsigned char*);
	setNext(pChunkHeader,m_pHead);
	m_pHead = pChunkHeader;
}


void MemMgr::destroy()
{
	for (int i=0; i<m_nBlocks; i++) std::free(m_ppMemBlocks[i]);
	std::free(m_ppMemBlocks);
	reset();
}

MemMgr::~MemMgr()
{
	destroy();
}