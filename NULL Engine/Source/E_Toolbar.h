#ifndef __E_TOOLBAR_H__
#define __E_TOOLBAR_H__

#include "EditorPanel.h"

class E_Toolbar : public EditorPanel
{
public:
	E_Toolbar();
	~E_Toolbar();
	void PlayAndStopButtons();
	void TimeDisplays();
	bool Draw(ImGuiIO& io) override;
	bool CleanUp() override;

private:


};

#endif // !__E_TOOLBAR_H__