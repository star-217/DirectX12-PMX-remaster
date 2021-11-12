#pragma once

#include "PmxStructList.h"

class PmxReading {
public:
	PmxData PmxRead(const char*);

private:
	//���f����񃍁[�h
	void Header(FILE* fp);
	void Vertex(FILE* fp);
	void Surface(FILE* fp);
	void Texture(FILE* fp);
	void Material(FILE* fp);
	void Born(FILE* fp);

	bool GetPMXStringUTF16(FILE* file, std::wstring& output);
	//! �t�@�C���p�X
	std::wstring m_ps;

	PmxData m_data;

};