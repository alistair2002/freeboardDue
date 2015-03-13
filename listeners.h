#include "freeboardDue.h"

/* this class is passed references to the two sentence pools one to claim
   empty buffers from and one to pass them to when they are filled */
class serialHandler {

public:

	serialHandler (SentenceQueue *freeQue, SentenceQueue *procQue)
	{
		this->freeQue = freeQue;
		this->procQue = procQue;
		this->fillBuffer = NULL;
		this->fillPos = 0;
	}

	~serialHandler ()
	{
		if (NULL != this->fillBuffer)
		{
			freeQue->push(this->fillBuffer);
			this->fillBuffer = NULL;
		}
		fillPos = 0;
	}

	void queueChar( char c )
	{
		/* bail on control characters including \n, \r etc */
		if (('\n' == c ) or ('\r' == c ))//iscntrl(c))
		{
			if ((NULL != this->fillBuffer)&&
				(0 != this->fillPos))
			{
				this->procQue->push(this->fillBuffer);
				this->fillBuffer = NULL;
				this->fillPos = 0;
			}
		}
		else
		{
			if ((NULL == this->fillBuffer)&&
				(NULL != this->freeQue))
			{
				this->fillBuffer = this->freeQue->pop();
				this->fillPos = 0;
			}
			
			if (NULL != this->fillBuffer)
			{
				if (MAX_SENTENCE_LENGTH > this->fillPos)
				{
					this->fillBuffer[this->fillPos++] = c;
				}
				
				/* wrap to avoid overflow of runaway sentences */
				if (MAX_SENTENCE_LENGTH == this->fillPos)
				{
					this->fillPos = 0;
				}
				this->fillBuffer[this->fillPos] = '\0';
			}
		}
	}

private:

	SentenceQueue *freeQue;
	SentenceQueue *procQue;

	char 		*fillBuffer;
	unsigned int fillPos;
};
