#pragma once
#include <iostream>
class QualityCheck
{
private:
	int m_threshold;
public:
	QualityCheck() : m_threshold() {}
	int getThreshold();
	void setThreshold();
};

