#ifndef BUFFERTYPE_H_INCLUDE
#define BUFFERTYPE_H_INCLUDE

class BufferType
{public:
	char m_character;
	unsigned int m_bits;

	BufferType();
	~BufferType();

	void initBuffer();
};
BufferType::BufferType() {
	initBuffer();
}
BufferType::~BufferType() {

}
void BufferType::initBuffer()
{
	m_character = 0;
	m_bits = 0;
}

#endif // !BUFFERTYPE_H_INCLUDE
