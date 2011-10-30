#ifndef __UBERMANAGER_H__
#define __UBERMANAGER_H__

#include <string>

struct EffectState;

class UberShader
{
public:
	UberShader (const std::string& vertShader, const std::string& fragShader);
	~UberShader ();

	void SetEffectState (const EffectState& effectState);
private:



};

#endif