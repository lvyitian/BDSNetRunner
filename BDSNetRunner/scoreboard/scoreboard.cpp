#include "scoreboard.hpp"
#include "../mod.h"

#if (MODULE_05007)

Scoreboard* scoreboard;//����Ʒְ�����

//��ȡ�����ָ���Ʒְ��µ����ݣ�����������������Ʒְ��������ҵ�ֵ��
int getscoreboard(Player* p, std::string objname) {
	auto testobj = scoreboard->getObjective(objname);
	if (!testobj) {
		std::cout << u8"[CSR] δ���ҵ���Ӧ�Ʒְ壬�Զ�������" << objname << std::endl;
		testobj = scoreboard->addObjective(objname, objname);
		return 0;
	}
	__int64 a2[2];
	auto scoreid = scoreboard->getScoreboardID(p);
	auto scores = ((Objective*)testobj)->getplayerscoreinfo((ScoreInfo*)a2, scoreid);
	return scores->getcount();
}

bool setscoreboard(Player* p, std::string objname, int count) {
	auto testobj = scoreboard->getObjective(objname);
	if (!testobj) {
		std::cout << u8"[CSR] δ���ҵ���Ӧ�Ʒְ壬�Զ�����: " << objname << std::endl;
		testobj = scoreboard->addObjective(objname, objname);
	}
	if (!testobj)
		return false;
	VA scoreid = (VA)scoreboard->getScoreboardID(p);
	if (scoreid == (VA)SYM_POINT(VA, MSSYM_B1QA7INVALIDB1AE12ScoreboardIdB2AAA32U1B1AA1A)) {
		std::cout << u8"[CSR] δ���ҵ���Ҷ�Ӧ�Ʒְ壬�Զ�����: " << objname << std::endl;
		scoreid = scoreboard->createPlayerScoreboardId(p);
	}
	if (!scoreid || scoreid == (VA)SYM_POINT(VA, MSSYM_B1QA7INVALIDB1AE12ScoreboardIdB2AAA32U1B1AA1A))
		return false;
	scoreboard->modifyPlayerScore((ScoreboardId*)scoreid, (Objective*)testobj, count);
	return true;
}

// �Ʒְ�����ע�ᣨ����ʱ��ȡ���еļƷְ����ƣ�
THook(void*, MSSYM_B2QQE170ServerScoreboardB2AAA4QEAAB1AE24VCommandSoftEnumRegistryB2AAE16PEAVLevelStorageB3AAAA1Z, void* _this, void* a2, void* a3) {
	scoreboard = (Scoreboard*)original(_this, a2, a3);
	return scoreboard;
}

#endif
