/***************************************************
**	ģ�鹦��:	�����û����潻��
**	ģ������:	interface.c
**	���ߣ�		�α���
****************************************************
*/
#include "user.h"
#include "GUI.h"
#include "EDIT.h"
#include "logic.h"
#include "lib.h"
#include "db.h"
#include "interface.h"

/************************************************************************/
/* widget����Ⱥ                                                         */
/************************************************************************/
//����������������
static const GUI_WIDGET_CREATE_INFO widgetMainFrame[] =
{
    { FRAMEWIN_CreateIndirect,  "����������������", GUI_ID_USER,     	0,0,CL998_LCD_XLEN,CL998_LCD_YLEN,0,0 }, 
    { BUTTON_CreateIndirect,    "�������ü�����",   GUI_ID_BUTTON0,     40,10,150,60,0},
    { BUTTON_CreateIndirect,    "��Ϣ��ѯ���༭",   GUI_ID_BUTTON1,     40,90,150,60,0},
    { BUTTON_CreateIndirect,    "ϵͳ����",         GUI_ID_BUTTON2,     40,170,150,60,0}
};

//�������ü����ƽ���
static const GUI_WIDGET_CREATE_INFO widgetSetParaAndControl[] =
{
    { FRAMEWIN_CreateIndirect,  "�������ü�����",   CONFIG_FRAME_IDX,   0,0,CL998_LCD_XLEN,CL998_LCD_YLEN,0,0 }, 
    { BUTTON_CreateIndirect,    "Уʱ",             GUI_ID_BUTTON0,     5,5,105,60,0},
    { BUTTON_CreateIndirect,    "������ʱ",         GUI_ID_BUTTON1,     130,5,105,60,0},
    { BUTTON_CreateIndirect,    "�޸ļ�������",     GUI_ID_BUTTON2,     5,75,105,60,0},
    { BUTTON_CreateIndirect,    "GPRS����",         GUI_ID_BUTTON3,     130,75,105,60,0},
    { BUTTON_CreateIndirect,    "��������",         GUI_ID_BUTTON4,     5,145,105,60,0},
    { BUTTON_CreateIndirect,    "������Ϣ",         GUI_ID_BUTTON5,     130,145,105,60,0},
    { BUTTON_CreateIndirect,    "������Ϣ�޸�",     GUI_ID_BUTTON6,     5,215,105,60,0},
    { BUTTON_CreateIndirect,    "����������",       GUI_ID_BUTTON7,     130,215,105,60,0}
};

//��������Уʱ
static const GUI_WIDGET_CREATE_INFO widgetSetTime[] =
{
	{ FRAMEWIN_CreateIndirect,  "Уʱ",		CONFIG_CTIME_FRAME_IDX,		0,0,CL998_LCD_XLEN,CL998_LCD_YLEN,0,0 },
	{ BUTTON_CreateIndirect,    "��������",	GUI_ID_BUTTON0,             10,26,80,30,0 },
	{ EDIT_CreateIndirect,      "",			GUI_ID_EDIT0,               108,26,110,30,0 },
	{ BUTTON_CreateIndirect,    "�˳�",		GUI_ID_BUTTON1,             10,221,80,30,0 },
	{ BUTTON_CreateIndirect,    "Уʱ",		GUI_ID_BUTTON2,             138,221,80,30,0 }
};

//������Ϣ�·�
static const GUI_WIDGET_CREATE_INFO widgetBaseInfoIssue[] =
{
    { FRAMEWIN_CreateIndirect,  "������Ϣ�·�",	CONFIG_BASE_INFO_FRAME_IDX, 0,0,CL998_LCD_XLEN,CL998_LCD_YLEN,0,0 }, 
    { BUTTON_CreateIndirect,    "��������",		GUI_ID_BUTTON0,             10,26,80,30,0},
    { EDIT_CreateIndirect,      "",				GUI_ID_EDIT0,               108,26,110,30,0},
    { BUTTON_CreateIndirect,    "�˳�",			GUI_ID_BUTTON1,             10,221,80,30,0},
    { BUTTON_CreateIndirect,    "�·�",			GUI_ID_BUTTON2,             138,221,80,30,0}
};

//������Ϣ�޸�
static const GUI_WIDGET_CREATE_INFO widgetModifyMeterInfo[] = {
	{ FRAMEWIN_CreateIndirect, "������Ϣ�޸�", CONFIG_BASE_INFO_MODIFY_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 95, 4, 66, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 95, 32, 68, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON2, 4, 265, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�·�", GUI_ID_BUTTON3, 141, 265, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "������", GUI_ID_BUTTON0, 4, 3, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", GUI_ID_TEXT0, 4, 34, 71, 17, 0, 0 },
	{ BUTTON_CreateIndirect, "��ѯ", GUI_ID_BUTTON1, 172, 5, 48, 45, 0, 0 },

	{ TEXT_CreateIndirect, "������", TEXT_MODIFY_1INFO_ROWID, 4, 67, 48, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_ROWID, 65, 66, 53, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_METERADDR, 4, 93, 46, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_METERADDR, 65, 90, 145, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_VENDORID, 4, 115, 48, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_VENDORID, 65, 114, 33, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�汾", TEXT_MODIFY_1INFO_PROTOVER, 128, 65, 42, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_PROTOVER, 181, 64, 30, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", TEXT_MODIFY_1INFO_METERTYPE, 109, 114, 50, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_METERTYPE, 180, 113, 29, 20, 0, 0 },
	{ TEXT_CreateIndirect, "ͨ��", TEXT_MODIFY_1INFO_CHANNEL, 4, 141, 49, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_CHANNEL, 65, 140, 34, 20, 0, 0 },
	{ TEXT_CreateIndirect, "���ذ汾", TEXT_MODIFY_1INFO_VALVEPROTOVER, 113, 140, 65, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_VALVEPROTOVER, 180, 140, 30, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_VALVEADDR, 4, 166, 54, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_VALVEADDR, 65, 164, 145, 20, 0, 0 },
	{ TEXT_CreateIndirect, "���", TEXT_MODIFY_1INFO_CONTROLPANELADDR, 4, 188, 36, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_CONTROLPANELADDR, 65, 190, 145, 20, 0, 0 },
	{ TEXT_CreateIndirect, "¥��", TEXT_MODIFY_1INFO_BUILDID, 4, 211, 36, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_BUILDID, 65, 212, 42, 20, 0, 0 },
	{ TEXT_CreateIndirect, "��Ԫ", TEXT_MODIFY_1INFO_UNITID, 119, 214, 36, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_UNITID, 162, 214, 48, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_ROOMID, 4, 238, 42, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_ROOMID, 65, 235, 53, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetTimeNodes[] = {
	{ FRAMEWIN_CreateIndirect, "����ʱ���", CONFIG_TNODE_FRAME_IDX, 0, 1, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ TEXT_CreateIndirect, "��ʼʱ��", GUI_ID_TEXT0, 15, 18, 47, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", GUI_ID_TEXT1, 13, 42, 48, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 77, 15, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 77, 40, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "����", GUI_ID_BUTTON0, 172, 15, 49, 42, 0, 0 },
	{ MULTIEDIT_CreateIndirect, "", GUI_ID_MULTIEDIT0, 14, 73, 200, 121, 0, 0 },
	{ BUTTON_CreateIndirect, "������", GUI_ID_BUTTON1, 15, 220, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT2, 126, 220, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON2, 10, 260, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�·�", GUI_ID_BUTTON3, 126, 260, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetModifyGatewayId[] = {
	{ FRAMEWIN_CreateIndirect, "�޸ļ��������", CONFIG_MODIFY_GATEWAYNO_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "ԭ���", GUI_ID_BUTTON0, 10, 30, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 125, 31, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 125, 80, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON1, 9, 260, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�޸�", GUI_ID_BUTTON2, 146, 260, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�ֱ��", GUI_ID_TEXT0, 10, 82, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetModifyGPRS[] = {
	{ FRAMEWIN_CreateIndirect, "�޸�GPRS����", CONFIG_GPRS_PARASET_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 15, 12, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "IP", GUI_ID_TEXT0, 30, 45, 50, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�˿ں�", GUI_ID_TEXT1, 15, 75, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "APN", GUI_ID_TEXT2, 15, 105, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��ȡ", GUI_ID_BUTTON1, 15, 159, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON2, 15, 260, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�޸�", GUI_ID_BUTTON3, 129, 260, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 130, 12, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 80, 45, 130, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT2, 130, 75, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT3, 130, 105, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetReboot[] = {
	{ FRAMEWIN_CreateIndirect, "����������", CONFIG_REBOOT_GATEWAY_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 15, 20, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 130, 20, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON1, 13, 245, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "����", GUI_ID_BUTTON2, 130, 245, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetRereadParam[] = {
	{ FRAMEWIN_CreateIndirect, "��������", CONFIG_REREAD_PARASET_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 15, 20, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 130, 20, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON1, 13, 245, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�·�", GUI_ID_BUTTON2, 130, 245, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�ȱ���������", GUI_ID_TEXT0, 15, 60, 110, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�ȱ��������", GUI_ID_TEXT1, 15, 100, 110, 20, 0, 0 },
	{ TEXT_CreateIndirect, "���ز�������", GUI_ID_TEXT2, 15, 140, 110, 20, 0, 0 },
	{ TEXT_CreateIndirect, "���ز������", GUI_ID_TEXT3, 15, 180, 110, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 130, 60, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT2, 130, 100, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT3, 130, 140, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT4, 130, 180, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetQueryEditInfo[] = {
	{ FRAMEWIN_CreateIndirect, "��Ϣ��ѯ��༭", INFOQ_EDIT_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 15, 30, 80, 60, 0, 0 },
	{ BUTTON_CreateIndirect, "��ʷ����", GUI_ID_BUTTON1, 130, 30, 80, 60, 0, 0 },
	{ BUTTON_CreateIndirect, "����ַ", GUI_ID_BUTTON2, 15, 120, 80, 60, 0, 0 },
	{ BUTTON_CreateIndirect, "������\nʷ����", GUI_ID_BUTTON3, 130, 120, 80, 60, 0, 0 },
	{ BUTTON_CreateIndirect, "�汾��ѯ", GUI_ID_BUTTON4, 15, 210, 80, 60, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetReadMeterImmd[] = {
	{ FRAMEWIN_CreateIndirect, "��������", INFOQ_READ_IMDT_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 15, 30, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 130, 30, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON1, 15, 260, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON2, 132, 260, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetQueryVersion[] = {
	{ FRAMEWIN_CreateIndirect, "�汾��ѯ", INFOQ_VER_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 15, 30, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON1, 15, 240, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��ѯ", GUI_ID_BUTTON2, 134, 240, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 130, 30, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�����汾", GUI_ID_TEXT0, 15, 85, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "Ӳ���汾", GUI_ID_TEXT1, 15, 135, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 130, 85, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT2, 130, 135, 80, 20, 0, 0 }
};

//��ȡ������Ϣ
static const GUI_WIDGET_CREATE_INFO widgetReadBaseInfo[] = {
	{ FRAMEWIN_CreateIndirect, "��ȡ������Ϣ", CONFIG_BASE_INFO_MODIFY_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 95, 4, 66, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "������", GUI_ID_BUTTON0, 4, 3, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "���µ�����", GUI_ID_BUTTON4, 4, 34, 130, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��ȡ", GUI_ID_BUTTON1, 172, 5, 48, 45, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON2, 4, 265, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��һ��", GUI_ID_BUTTON3, 141, 265, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", TEXT_MODIFY_1INFO_ROWID, 4, 67, 48, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_ROWID, 65, 66, 53, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_METERADDR, 4, 93, 46, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_METERADDR, 65, 90, 145, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_VENDORID, 4, 115, 48, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_VENDORID, 65, 114, 33, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�汾", TEXT_MODIFY_1INFO_PROTOVER, 128, 65, 42, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_PROTOVER, 181, 64, 30, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", TEXT_MODIFY_1INFO_METERTYPE, 109, 114, 50, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_METERTYPE, 180, 113, 29, 20, 0, 0 },
	{ TEXT_CreateIndirect, "ͨ��", TEXT_MODIFY_1INFO_CHANNEL, 4, 141, 49, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_CHANNEL, 65, 140, 34, 20, 0, 0 },
	{ TEXT_CreateIndirect, "���ذ汾", TEXT_MODIFY_1INFO_VALVEPROTOVER, 113, 140, 65, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_VALVEPROTOVER, 180, 140, 30, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_VALVEADDR, 4, 166, 54, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_VALVEADDR, 65, 164, 145, 20, 0, 0 },
	{ TEXT_CreateIndirect, "���", TEXT_MODIFY_1INFO_CONTROLPANELADDR, 4, 188, 36, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_CONTROLPANELADDR, 65, 190, 145, 20, 0, 0 },
	{ TEXT_CreateIndirect, "¥��", TEXT_MODIFY_1INFO_BUILDID, 4, 211, 36, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_BUILDID, 65, 212, 42, 20, 0, 0 },
	{ TEXT_CreateIndirect, "��Ԫ", TEXT_MODIFY_1INFO_UNITID, 119, 214, 36, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_UNITID, 162, 214, 48, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", TEXT_MODIFY_1INFO_ROOMID, 4, 238, 42, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", EDIT_MODIFY_1INFO_ROOMID, 65, 235, 53, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetHisData[] = {
	{ FRAMEWIN_CreateIndirect, "��ʷ���ݲ�ѯ", INFOQ_HISDATA_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 10, 10, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 130, 10, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON1, 10, 275, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��ȡ", GUI_ID_BUTTON2, 134, 275, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�ɹ���", GUI_ID_TEXT0, 10, 45, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "ʧ����", GUI_ID_TEXT1, 10, 80, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "�ɹ���", GUI_ID_TEXT2, 10, 115, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 130, 45, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT2, 130, 80, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT3, 130, 115, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "�ɹ�\n�굥", GUI_ID_BUTTON3, 10, 190, 60, 60, 0, 0 },
	{ BUTTON_CreateIndirect, "ʧ��\n�굥", GUI_ID_BUTTON4, 150, 190, 60, 60, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetHisSheet[] = {
	{ FRAMEWIN_CreateIndirect, "��ϸ�嵥", INFOQ_HISDATA_SHEET_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 130, 10, 80, 20, 0, 0 },
	{ LISTVIEW_CreateIndirect, "�굥", GUI_ID_LISTVIEW0, 5, 35, 220, 227, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON0, 10, 275, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��һ��", GUI_ID_BUTTON1, 134, 275, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����", GUI_ID_TEXT0, 10, 10, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetRemote1Meter[] = {
	{ FRAMEWIN_CreateIndirect, "͸������������", INFOQ_SINGLE_READ_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ BUTTON_CreateIndirect, "��������", GUI_ID_BUTTON0, 10, 5, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 125, 5, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", GUI_ID_TEXT0, 10, 35, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 125, 35, 80, 20, 0, 0 },
	{ LISTVIEW_CreateIndirect, "", GUI_ID_LISTVIEW0, 13, 78, 201, 169, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON1, 10, 270, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "��ȡ", GUI_ID_BUTTON2, 130, 270, 80, 20, 0, 0 }
};

static const GUI_WIDGET_CREATE_INFO widgetDeviceConfig[] = {
	{ FRAMEWIN_CreateIndirect, "�ֳֻ�����", COM_CONFIG_FRAME_IDX, 0, 0, CL998_LCD_XLEN, CL998_LCD_YLEN, 0, 0 },
	{ TEXT_CreateIndirect, "�˿�", GUI_ID_TEXT0, 10, 10, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "������", GUI_ID_TEXT1, 10, 40, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "����λ", GUI_ID_TEXT2, 10, 70, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "У��λ", GUI_ID_TEXT3, 11, 100, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "ֹͣλ", GUI_ID_TEXT4, 10, 130, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "��������", GUI_ID_TEXT5, 10, 160, 80, 20, 0, 0 },
	{ TEXT_CreateIndirect, "��������", GUI_ID_TEXT6, 10, 190, 80, 20, 0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", GUI_ID_DROPDOWN0, 136, 10, 80, 19, 0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", GUI_ID_DROPDOWN1, 135, 40, 80, 19, 0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", GUI_ID_DROPDOWN2, 135, 70, 80, 19, 0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", GUI_ID_DROPDOWN3, 135, 100, 80, 19, 0, 0 },
	{ DROPDOWN_CreateIndirect, "Dropdown", GUI_ID_DROPDOWN4, 135, 130, 80, 19, 0, 0 },
	{ BUTTON_CreateIndirect, "�˳�", GUI_ID_BUTTON0, 10, 265, 80, 20, 0, 0 },
	{ BUTTON_CreateIndirect, "����", GUI_ID_BUTTON1, 135, 265, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT0, 135, 160, 80, 20, 0, 0 },
	{ EDIT_CreateIndirect, "", GUI_ID_EDIT1, 135, 190, 80, 20, 0, 0 }
};

static U8 gu8success = NO_ERR;
static U8 gu8hasReadHisData = ERROR;
static U16	gu16sucCnt = 0;
static U16	gu16failCnt = 0;

S8* gs8deviceStrArray[] = { "RS485","MBUS" };

U8	gu8deviceIntArray[] = { UART_DEVICE_RS485, UART_DEVICE_MBUS };

S8* gs8baudStrArray[] = { "1200","2400","4800","9600","19200","38400","57600","115200" };

U32 gu32baudIntArray[] = { 1200,2400,4800,9600,19200,38400,57600,115200 };

S8* gs8databitStrArray[] = {"8", "7", "9"};

S8* gs8parityStrArray[] = {"��",	 "��", "ż"};

S8* gs8stopStrArray[] = {"1"};

uart_mode_str	gUart_mode_strMap[] = {
{ em_databit_7, em_parity_odd, em_stop_1 },
{ em_databit_7, em_parity_even,em_stop_1 },
{ em_databit_8, em_parity_none,em_stop_1 },
{ em_databit_8, em_parity_odd, em_stop_1 },
{ em_databit_8, em_parity_even,em_stop_1 },
{ em_databit_9, em_parity_none,em_stop_1 } };

/************************************************************************/
/* Init����Ⱥ                                                           */
/************************************************************************/
//�Լ�����������������ʼ��
static void mainFrameInit( WM_HWIN hDlg )
{
    WM_HWIN pObj;
    pObj = WM_GetDialogItem( hDlg, GUI_ID_TEXT0);
    TEXT_SetTextAlign(pObj,GUI_TA_CENTER);
    TEXT_SetFont(pObj,GUI_GetFontAddress(24));
  	WM_MakeModal( hDlg );                         //���öԻ���Ϊ��ռģʽ
  	WM_SetFocus( hDlg );                          //��ϵͳ���㶨λ���Ի�����
}

//�Բ�����������ƽ����ʼ��
static void setParaAndControlInit(WM_HWIN hDlg){}

//�Լ�����Уʱ�����ʼ��
static void setTimeInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
	EDIT_SetMaxLen(hItem, 2 * GATEWAY_OADD_LEN);
}

//�Ի�����Ϣ�·������ʼ��
static void baseInfoIssueInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}

//���޸Ļ�����Ϣ�����ʼ��
static void ModifyOneInfoInit(WM_HWIN hDlg)
{
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };
	WM_HWIN hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERADDR);
	EDIT_SetMaxLen(hItem, 2 * PROTO_LEN_MADDR);
	hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEADDR);
	EDIT_SetMaxLen(hItem, 2 * PROTO_LEN_MADDR);
	hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CONTROLPANELADDR);
	EDIT_SetMaxLen(hItem, 2 * PROTO_LEN_MADDR);

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}

static void setTimeNodesInit(WM_HWIN hDlg)
{
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };
	WM_HWIN hItem = WM_GetDialogItem(hDlg, GUI_ID_MULTIEDIT0);
	MULTIEDIT_SetWrapWord(hItem);

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT2);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}

static void modifyGatewayIdInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}

static void modifyGPRSInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_TEXT0);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_TEXT1);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_TEXT2);
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_SetMaxLen(hItem, 20);
}

static void rebootInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}

static void rereadInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}

static void queryEditInfoInit(WM_HWIN hDlg){}

static void queryVersionInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}

static void queryBaseInfoInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_BUTTON4);
	BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_RED);
	
	hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERADDR);
	EDIT_SetMaxLen(hItem, 2 * PROTO_LEN_MADDR);
	hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEADDR);
	EDIT_SetMaxLen(hItem, 2 * PROTO_LEN_MADDR);
	hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CONTROLPANELADDR);
	EDIT_SetMaxLen(hItem, 2 * PROTO_LEN_MADDR);
}

static void queryHisDataInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_SetMaxLen(hItem, 2*GATEWAY_OADD_LEN);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_SetMaxLen(hItem, 5);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT2);
	EDIT_SetMaxLen(hItem, 5);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT3);
	EDIT_SetMaxLen(hItem, 6);
}

static void hisSheetInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	db_hisdata_str dbHisStr = { 0 };
	U8	count[5] = { 0 };

	hItem = WM_GetDialogItem(hDlg, GUI_ID_TEXT0);
	if (gu8success == NO_ERR) {
		TEXT_SetText(hItem, "�ɹ�����");
	} else {
		TEXT_SetText(hItem, "ʧ�ܸ���");
	}
	TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_LISTVIEW0);
	LISTVIEW_AddColumn(hItem, 80, "��Ŀ", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddColumn(hItem, 135, "ֵ", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_id, "������");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_maddr, "����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_build, "¥��");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_unit, "��Ԫ��");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_room, "�����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_intemp, "��ˮ�¶�");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_outtemp, "��ˮ�¶�");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_flow, "����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_heat, "����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_roomtemp, "�����¶�");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_vopen, "���ſ���");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_fsuc, "�ɹ���־");
	LISTVIEW_SetGridVis(hItem, 1);

	logic_initHisView(&dbHisStr, gu8success);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_id, (const char*)dbHisStr.id);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_maddr, (const char*)dbHisStr.maddr);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_build, (const char*)dbHisStr.build);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_unit, (const char*)dbHisStr.unit);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_room, (const char*)dbHisStr.room);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_intemp, (const char*)dbHisStr.intemp);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_outtemp, (const char*)dbHisStr.outtemp);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_flow, (const char*)dbHisStr.flow);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_heat, (const char*)dbHisStr.heat);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_roomtemp, (const char*)dbHisStr.roomtemp);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_vopen, (const char*)dbHisStr.vopen);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_fsuc, (const char*)dbHisStr.fsuc);

	Lib_sprintf((char*)count, "%d", gu8success == NO_ERR ? gu16sucCnt : gu16failCnt);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_SetText(hItem, (const char*)count);
}

static void remote1MeterInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_gateway_id, lu8gwyAdd);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_LISTVIEW0);
	LISTVIEW_AddColumn(hItem, 80, "��Ŀ", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddColumn(hItem, 135, "ֵ", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_AddRow(hItem, NULL);
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_id, "������");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_maddr, "����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_build, "¥��");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_unit, "��Ԫ��");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_room, "�����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_intemp, "��ˮ�¶�");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_outtemp, "��ˮ�¶�");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_flow, "����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_heat, "����");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_roomtemp, "�����¶�");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_vopen, "���ſ���");
	LISTVIEW_SetItemText(hItem, LISTVIEW_COL_ITEM, em_filedidx_fsuc, "�ɹ���־");
	LISTVIEW_SetGridVis(hItem, 1);
}

static void deviceConfigInit(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U16 i = 0;
	sUART lComConfig;//com config
	U8 lu8svrAdd[GATEWAY_SADD_LEN] = { 0 };//��վ���, �����
	U8 lu8gwyAdd[GATEWAY_OADD_LEN] = { 0 };//���������, �����
	S8 tmpStr[10] = { 0 };

	db_getCongfig(config_com_para, (U8*)&lComConfig);
	db_getCongfig(config_gateway_id, lu8gwyAdd);
	db_getCongfig(config_server_id, lu8svrAdd);

	for (i = GUI_ID_TEXT0; i <= GUI_ID_TEXT6;i++) {
		hItem = WM_GetDialogItem(hDlg, i);
		TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	}

	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN0);
	for (i = 0; i < sizeof(gs8deviceStrArray) / sizeof(S8*); i++) {
		DROPDOWN_AddString(hItem, gs8deviceStrArray[i]);
		if (gu8deviceIntArray[i] == lComConfig.device) {
			DROPDOWN_SetSel(hItem, i);
		}
	}

	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN1);
	for (i = 0; i < sizeof(gs8baudStrArray) / sizeof(S8*); i++) {
		DROPDOWN_AddString(hItem, gs8baudStrArray[i]);
		if (gu32baudIntArray[i] == lComConfig.baud) {
			DROPDOWN_SetSel(hItem, i);
		}
	}

	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN2);
	for (i = 0; i < sizeof(gs8databitStrArray) / sizeof(S8*); i++) {
		DROPDOWN_AddString(hItem, gs8databitStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, gUart_mode_strMap[lComConfig.mode - 1].databit);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN3);
	for (i = 0; i < sizeof(gs8parityStrArray) / sizeof(S8*); i++) {
		DROPDOWN_AddString(hItem, gs8parityStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, gUart_mode_strMap[lComConfig.mode - 1].parity);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN4);
	for (i = 0; i < sizeof(gs8stopStrArray) / sizeof(S8*); i++) {
		DROPDOWN_AddString(hItem, gs8stopStrArray[i]);
	}
	DROPDOWN_SetSel(hItem, gUart_mode_strMap[lComConfig.mode - 1].stop);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	Lib_sprintf(tmpStr, "%02x%02x", lu8gwyAdd[1], lu8gwyAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	Lib_sprintf(tmpStr, "%02x%02x", lu8svrAdd[1], lu8svrAdd[0]);
	EDIT_SetText(hItem, (const char*)tmpStr);
}
/************************************************************************/
/* CallBack����Ⱥ                                                       */
/************************************************************************/
//������Ļص�����
void mainCb( WM_MESSAGE* pMsg )
{
    int NCode, Id, keyId;
    WM_HWIN hDlg;

    hDlg = pMsg->hWin;

    switch ( pMsg->MsgId )
    {
    case WM_INIT_DIALOG:
        mainFrameInit(hDlg);
    break;
    case WM_PAINT:
        break;
    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);   
        NCode = pMsg->Data.v;        
        switch (NCode)
        {
        case WM_NOTIFICATION_RELEASED: //��������Ϣ
            GUI_EndDialog(hDlg, Id);
            break;
        default:
            break;
        }
    break;
    case WM_KEY: //������Ϣ
        keyId = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
        switch ( keyId )
        {
        case GUI_KEY_ESCAPE:
            GUI_EndDialog( hDlg, -1 );
            break;
        case GUI_KEY_UP:
            WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem( hDlg, GUI_ID_BUTTON0)));
            break;
        case GUI_KEY_DOWN:
            WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem( hDlg, GUI_ID_BUTTON0)));
            break;
        default:
            if(keyId>=GUI_KEY_NUM1 && keyId<=GUI_KEY_NUM3)
                GUI_EndDialog( hDlg, keyId+(GUI_ID_BUTTON0-GUI_KEY_NUM0)-1);//�ð���"1"��Ӧbutton0
            break;
        }
        break;
    default:
        WM_DefaultProc( pMsg );
        break;
    }
}

//������������ƽ���Ļص�����
void setParaAndControlCb( WM_MESSAGE* pMsg )
{
    int NCode, Id, keyId;
    WM_HWIN hDlg;

    hDlg = pMsg->hWin;

    switch ( pMsg->MsgId )
    {
    case WM_INIT_DIALOG:
        setParaAndControlInit(hDlg);
    break;
    case WM_PAINT:
    break;  
    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);   
        NCode = pMsg->Data.v;        
        switch (NCode)
        {
        case WM_NOTIFICATION_RELEASED: //��������Ϣ
            GUI_EndDialog(hDlg, Id); 
            break;
        default:
            break;
        }
    break;
    case WM_KEY: //������Ϣ
        keyId = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
        switch (keyId)
        {
        case GUI_KEY_ESCAPE:
            GUI_EndDialog( hDlg, -1 );
            break;
        case GUI_KEY_UP:
            WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem( hDlg, GUI_ID_BUTTON0)));
            break;
        case GUI_KEY_DOWN:
            WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem( hDlg, GUI_ID_BUTTON0)));
            break;
        default:
            if(keyId>=GUI_KEY_NUM1 && keyId<=GUI_KEY_NUM8)
                GUI_EndDialog( hDlg, keyId+(GUI_ID_BUTTON0-GUI_KEY_NUM0)-1);//�ð���"1"��Ӧbutton0
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}

void userSetTime(WM_HWIN hObj)
{
	U8 lu8InputBuf[EDIT_MAX_LEN] = { 0 };
	U8 lu8gatewayId[EDIT_MAX_LEN] = { 0 };

	EDIT_GetText(hObj, (char*)lu8InputBuf, EDIT_MAX_LEN);

	trimSpace(lu8InputBuf, EDIT_MAX_LEN);
	if (isNumber(lu8InputBuf, STRLEN(lu8InputBuf)) == ERROR) {
		GUI_MessageBox("\n����������!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}

	supplementTo12(lu8InputBuf);
	inverseStrToBCD(lu8InputBuf, 2 * GATEWAY_OADD_LEN, lu8gatewayId, GATEWAY_OADD_LEN);

	if (logic_setTime(lu8gatewayId) == NO_ERR) {
		GUI_MessageBox("\n����ʱ��ɹ�!\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hObj);
	}
	else {
		GUI_MessageBox("\n����ʱ��ʧ��!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	}
}

void radioReadGatewayId(WM_HWIN hObj)
{
	U8 gatewayId[GATEWAY_OADD_LEN] = { 0 };
	char gatewayStr[2 * GATEWAY_OADD_LEN] = { 0 };
	logic_readGatewayId(gatewayId);
	Lib_sprintf(gatewayStr, "%02X%02X%02X%02X%02X%02X", \
		gatewayId[0], gatewayId[1], gatewayId[2], \
		gatewayId[3], gatewayId[4], gatewayId[5]);
	trimZero((U8*)gatewayStr, 2 * GATEWAY_OADD_LEN);
	EDIT_SetText(hObj, gatewayStr);
}

void setTimeCb(struct WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		setTimeInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id)	{
			case GUI_ID_BUTTON0://radio read gateway's Id
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://Exit
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://�·�������ʱ��
				userSetTime(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			default:
				break;
			}
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://radio read gateway's Id
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM3://�·�������ʱ��
			userSetTime(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_ENTER:
			userSetTime(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}	
}

void userIssueInfo(WM_HWIN hObj)
{
	U8 lu8InputBuf[EDIT_MAX_LEN] = { 0 };

	EDIT_GetText(hObj, (char*)lu8InputBuf, EDIT_MAX_LEN);

	trimSpace(lu8InputBuf, EDIT_MAX_LEN);
	if (isNumber(lu8InputBuf, STRLEN(lu8InputBuf)) == ERROR) {
		GUI_MessageBox("\n����������!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}

	supplementTo12(lu8InputBuf);

	if (logic_issueMeterInfo(lu8InputBuf) == NO_ERR) {
		GUI_MessageBox("\n�·�����ַ�ɹ�!\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hObj);
	}
	else {
		GUI_MessageBox("\n�·�����ַʧ��!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	}
}

void baseInfoIssueCb(WM_MESSAGE* pMsg)
{
    int NCode, Id;
    WM_HWIN hDlg;

    hDlg = pMsg->hWin;

    switch ( pMsg->MsgId )
    {
    case WM_INIT_DIALOG:
        baseInfoIssueInit(hDlg);
		break;
    case WM_PAINT:
		break;  
    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);   
        NCode = pMsg->Data.v;        
        switch (NCode)
        {
        case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://radio read gateway's Id
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://Exit
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://�·��Ǳ�������Ϣ
				userIssueInfo(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			default:
				break;
			}
            break;
        default:
            break;
        }
		break;
    case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://radio read gateway's Id
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM3://�·�������ʱ��
			userIssueInfo(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_ENTER:
			userIssueInfo(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
    default:
        WM_DefaultProc(pMsg);
    }
}

void setListView(WM_HWIN hDlg, db_meterinfo_ptr pInfo)
{
	WM_HWIN hObj;

	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROWID);
	EDIT_SetText(hObj, (const char*)pInfo->rowId);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERADDR);
	EDIT_SetText(hObj, (const char*)pInfo->meterAddr);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VENDORID);
	EDIT_SetText(hObj, (const char*)pInfo->vendorId);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_PROTOVER);
	EDIT_SetText(hObj, (const char*)pInfo->protoVer);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERTYPE);
	EDIT_SetText(hObj, (const char*)pInfo->meterType);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CHANNEL);
	EDIT_SetText(hObj, (const char*)pInfo->channel);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEPROTOVER);
	EDIT_SetText(hObj, (const char*)pInfo->valveProtoVer);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEADDR);
	EDIT_SetText(hObj, (const char*)pInfo->valveAddr);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CONTROLPANELADDR);
	EDIT_SetText(hObj, (const char*)pInfo->controlPanelAddr);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_BUILDID);
	EDIT_SetText(hObj, (const char*)pInfo->buildId);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_UNITID);
	EDIT_SetText(hObj, (const char*)pInfo->unitId);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROOMID);
	EDIT_SetText(hObj, (const char*)pInfo->roomId);
}

void queryOneInfo(WM_HWIN hDlg)
{
	U8 lu8GatewayId[EDIT_MAX_LEN] = { 0 };
	U8 lu8MeterId[EDIT_MAX_LEN] = { 0 };
	db_meterinfo_str oneMeterInfoStr;
	WM_HWIN hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);

	EDIT_GetText(hObj, (char*)lu8GatewayId, EDIT_MAX_LEN);
	trimSpace(lu8GatewayId, STRLEN(lu8GatewayId));
	if (isNumber(lu8GatewayId, STRLEN(lu8GatewayId)) == ERROR) {
		GUI_MessageBox("\n����������������!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	if (STRLEN(lu8GatewayId) > DB_MINFO_LEN_GATEWAYID) {
		GUI_MessageBox("\n�������Ź���!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(lu8GatewayId);

	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_GetText(hObj, (char*)lu8MeterId, EDIT_MAX_LEN);
	trimSpace(lu8MeterId, STRLEN(lu8MeterId));
	if (isNumber(lu8MeterId, STRLEN(lu8MeterId)) == ERROR) {
		GUI_MessageBox("\n����������������!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}

	if (logic_queryOneMeterInfo(lu8GatewayId, Lib_atoi((char*)lu8MeterId), &oneMeterInfoStr) == NO_ERR) {
		setListView(hDlg, &oneMeterInfoStr);
	}
	else {
		GUI_MessageBox("\n��ѯ��������Ϣʧ��!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
	}
}

U8 readListView(WM_HWIN hDlg, db_meterinfo_ptr pInfo)
{
	WM_HWIN hObj;

	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROWID);
	EDIT_GetText(hObj, (char*)pInfo->rowId, DB_MINFO_LEN_ROWID + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERADDR);
	EDIT_GetText(hObj, (char*)pInfo->meterAddr, DB_MINFO_LEN_METERADDR + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VENDORID);
	EDIT_GetText(hObj, (char*)pInfo->vendorId, DB_MINFO_LEN_VENDORID + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_PROTOVER);
	EDIT_GetText(hObj, (char*)pInfo->protoVer, DB_MINFO_LEN_PROTOVER + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERTYPE);
	EDIT_GetText(hObj, (char*)pInfo->meterType, DB_MINFO_LEN_METERTYPE + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CHANNEL);
	EDIT_GetText(hObj, (char*)pInfo->channel, DB_MINFO_LEN_CHANNEL + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEPROTOVER);
	EDIT_GetText(hObj, (char*)pInfo->valveProtoVer, DB_MINFO_LEN_VALVEPROTOVER + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEADDR);
	EDIT_GetText(hObj, (char*)pInfo->valveAddr, DB_MINFO_LEN_VALVEADDR + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CONTROLPANELADDR);
	EDIT_GetText(hObj, (char*)pInfo->controlPanelAddr, DB_MINFO_LEN_CTLPANELADDR + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_BUILDID);
	EDIT_GetText(hObj, (char*)pInfo->buildId, DB_MINFO_LEN_BUILDID + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_UNITID);
	EDIT_GetText(hObj, (char*)pInfo->unitId, DB_MINFO_LEN_UNITID + 1);
	hObj = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROOMID);
	EDIT_GetText(hObj, (char*)pInfo->roomId, DB_MINFO_LEN_ROOMID + 1);


	return NO_ERR;
}

void userIssueOneInfo(WM_HWIN hDlg)
{
	WM_HWIN hObj;
	U8 lu8GatewayId[EDIT_MAX_LEN] = { 0 };
	db_meterinfo_str oneMeterInfoStr;

	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hObj, (char*)lu8GatewayId, EDIT_MAX_LEN);
	trimSpace(lu8GatewayId, STRLEN(lu8GatewayId));
	if (isNumber(lu8GatewayId, STRLEN(lu8GatewayId)) == ERROR) {
		GUI_MessageBox("\n����������!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(lu8GatewayId);

	if (readListView(hDlg, &oneMeterInfoStr) == ERROR) {
		return;
	}
	
	if (logic_issueOneMeterInfo(lu8GatewayId, &oneMeterInfoStr) == NO_ERR) {
		GUI_MessageBox("\n�޸ĵ������ݳɹ�!\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	else {
		GUI_MessageBox("\n�޸ĵ�������ʧ��!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void modifyOneInfoCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		ModifyOneInfoInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥��ȡ��������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://��DBF��ѯ��Ӧ������Ļ�����Ϣ
				queryOneInfo(hDlg);
				break;
			case GUI_ID_BUTTON2://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON3://�·������Ǳ�������Ϣ
				userIssueOneInfo(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥��ȡ��������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;		
		case GUI_KEY_NUM2://��DBF��ѯ��Ӧ������Ļ�����Ϣ
			queryOneInfo(hDlg);
			break;
		case GUI_KEY_NUM3://�·������Ǳ�������Ϣ
			userIssueOneInfo(hDlg);
			break;
		case GUI_KEY_NUM4://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_ENTER:
			userIssueOneInfo(hDlg);
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userGenTimeNodes(WM_HWIN hDlg)
{
	WM_HWIN hEdit;
	U8 startTime[10] = { 0 };
	U8 nodes[5] = { 0 };
	U8 bufTimeNodes[1024] = { 0 };

	hEdit = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hEdit, (char*)startTime, 10);
	if (timeLegal(startTime, STRLEN(startTime), NULL) == ERROR) {
		GUI_MessageBox("\n�������ʱ���ʽ����!\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	hEdit = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_GetText(hEdit, (char*)nodes, 5);
	if (isNumber(nodes, STRLEN(nodes)) == ERROR) {
		GUI_MessageBox("\nʱ������, ����������!\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	if (Lib_atoi((const char*)nodes) > 24) {
		GUI_MessageBox("\nʱ����������С��24!\n", "����", GUI_MESSAGEBOX_CF_MODAL);
	}
	if (logic_genTimeNodesStr(bufTimeNodes, 1024, startTime, Lib_atoi((const char*)nodes)) == ERROR) {
		GUI_MessageBox("\n����ʱ���ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	hEdit = WM_GetDialogItem(hDlg, GUI_ID_MULTIEDIT0);
	MULTIEDIT_SetText(hEdit, (const char*)bufTimeNodes);
}

void userIssueTimeNodes(WM_HWIN hDlg)
{
	WM_HWIN hEdit;
	U8 timeNodeBuf[128] = { 0 };
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1];

	hEdit = WM_GetDialogItem(hDlg, GUI_ID_MULTIEDIT0);
	MULTIEDIT_GetText(hEdit, (char*)timeNodeBuf, 128);

	if (logic_issueTimeNodes(timeNodeBuf, STRLEN(timeNodeBuf), gatewayId) == ERROR) {
		GUI_MessageBox("\n�·�����ʱ���ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		GUI_MessageBox("\n�·�����ʱ���ɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void setTimeNodesCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		setTimeNodesInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://���ɳ���ʱ���
				userGenTimeNodes(hDlg);
				break;
			case GUI_ID_BUTTON1://�㲥��ȡ��������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT2));
				break;
			case GUI_ID_BUTTON2://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON3://�·�����ʱ���
				userIssueTimeNodes(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://���ɳ���ʱ���
			userGenTimeNodes(hDlg);
			break;
		case GUI_KEY_NUM2://�㲥��ȡ��������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT2));
			break;
		case GUI_KEY_NUM3://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM4://�·�����ʱ���
			userIssueTimeNodes(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userModifyGatewayId(WM_HWIN hDlg)
{
	WM_HWIN hObj;
	U8	originalId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8	targetId[2 * GATEWAY_OADD_LEN + 1] = { 0 };

	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hObj, (char*)originalId, EDIT_MAX_LEN);
	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_GetText(hObj, (char*)targetId, EDIT_MAX_LEN);

	if ((isNumber(originalId, STRLEN(originalId))==ERROR) || (isNumber(targetId, STRLEN(targetId)) == ERROR)) {
		GUI_MessageBox("\n����������!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}

	supplementTo12(originalId);
	supplementTo12(targetId);
	if (logic_modifyGatewayId(originalId, targetId) == ERROR) {
		GUI_MessageBox("\n�޸ļ�������ʧ��!\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		GUI_MessageBox("\n�޸ļ������ųɹ�!\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void modifyGatewayIdCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		modifyGatewayIdInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://�޸ļ�������
				userModifyGatewayId(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT2));
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://�޸ļ�������
			userModifyGatewayId(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userQueryGPRS(WM_HWIN hDlg)
{
	WM_HWIN hObj;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8 apnId[3] = { 0 };
	U8 serverIp[20] = { 0 };
	U8 port[5] = { 0 };

	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);//������id
	EDIT_GetText(hObj, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(gatewayId);
	if (logic_readGPRSParam(gatewayId, apnId, serverIp, port) == ERROR) {
		GUI_MessageBox("\n��ȡ����\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);//ip��ַ
		EDIT_SetText(hObj, (const char*)serverIp);
		hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT2);//�˿ں�
		EDIT_SetText(hObj, (const char*)port);
		hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT3);//apn���
		EDIT_SetText(hObj, (const char*)apnId);
	}
	WM_SetFocus(hDlg);
}

void userModifyGPRS(WM_HWIN hDlg)
{
	WM_HWIN hObj;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8 apnId[3] = { 0 };
	U8 serverIp[20] = { 0 };
	U8 port[5] = { 0 };

	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);//������id
	EDIT_GetText(hObj, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);//ip��ַ
	EDIT_GetText(hObj, (char*)serverIp, 20);
	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT2);//�˿ں�
	EDIT_GetText(hObj, (char*)port, 5);
	hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT3);//apn���
	EDIT_GetText(hObj, (char*)apnId, 3);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR \
		|| isNumber(port, STRLEN(port)) == ERROR \
		|| isNumber(apnId, STRLEN(apnId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	if (IpLegal(serverIp, STRLEN(serverIp)) == ERROR) {
		GUI_MessageBox("\nIP��ַ�Ƿ�\n", "�Ƿ�", GUI_MESSAGEBOX_CF_MODAL);
		hObj = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);//ip��ַ
		EDIT_SetText(hObj, "");
		return;
	}
	supplementTo12(gatewayId);
	if(logic_modifyGPRSParam(gatewayId, apnId, serverIp, port) == ERROR)
		GUI_MessageBox("\n�޸�GPRS����ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	else
		GUI_MessageBox("\n�޸�GPRS�����ɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	WM_SetFocus(hDlg);
}

void modifyGPRSCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		modifyGPRSInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://��ѯ���в���
				userQueryGPRS(hDlg);
				break;
			case GUI_ID_BUTTON2://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON3://�޸Ĳ���
				userModifyGPRS(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT2));
			break;
		case GUI_KEY_NUM2://��ѯ���в���
			userQueryGPRS(hDlg);
			break;
		case GUI_KEY_NUM3://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM4://�޸Ĳ���
			userModifyGPRS(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userReboot(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(gatewayId);
	if (logic_reboot(gatewayId) == ERROR) {
		GUI_MessageBox("\n����������ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		GUI_MessageBox("\n5�������������\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void rebootCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		rebootInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://����
				userReboot(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://����
			userReboot(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userIssueRereadParam(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8 mReadCnt[3] = { 0 };//�ȱ���������
	U8 mReadIntv[7] = { 0 };//�ȱ��������
	U8 vReadCnt[3] = { 0 };//���ز�������
	U8 vReadIntv[7] = { 0 };//���ز������

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_GetText(hItem, (char*)mReadCnt, 3);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT2);
	EDIT_GetText(hItem, (char*)mReadIntv, 7);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT3);
	EDIT_GetText(hItem, (char*)vReadCnt, 3);
	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT4);
	EDIT_GetText(hItem, (char*)vReadIntv, 7);

	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR ||\
		isNumber(mReadCnt, STRLEN(mReadCnt)) == ERROR || \
		isNumber(mReadIntv, STRLEN(mReadIntv)) == ERROR || \
		isNumber(vReadCnt, STRLEN(vReadCnt)) == ERROR || \
		isNumber(vReadIntv, STRLEN(vReadIntv)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(gatewayId);
	if (logit_issueRereadParam(gatewayId, mReadCnt, mReadIntv, vReadCnt, vReadIntv) == ERROR) {
		GUI_MessageBox("\n����ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		GUI_MessageBox("\n���óɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void rereadCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		rereadInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://�·�
				userIssueRereadParam(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://�·�
			userIssueRereadParam(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

//������������ƽ���Ļص�����
void queryEditInfoCb(WM_MESSAGE* pMsg)
{
	int NCode, Id, keyId;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		queryEditInfoInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			GUI_EndDialog(hDlg, Id);
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		keyId = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
		switch (keyId)
		{
		case GUI_KEY_ESCAPE:
			GUI_EndDialog(hDlg, -1);
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			if (keyId >= GUI_KEY_NUM1 && keyId <= GUI_KEY_NUM8)
				GUI_EndDialog(hDlg, keyId + (GUI_ID_BUTTON0 - GUI_KEY_NUM0) - 1);//�ð���"1"��Ӧbutton0
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userReadMeterImmd(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(gatewayId);
	if (logic_readMeterImmd(gatewayId) == ERROR) {
		GUI_MessageBox("\n��������ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	}
	else {
		GUI_MessageBox("\n���������ɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void readMeterImmdCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		rereadInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://��������
				userReadMeterImmd(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://��������
			userReadMeterImmd(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userQueryVersion(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8 softVersion[10] = { 0 };//�ȱ���������
	U8 hardVersion[10] = { 0 };//�ȱ��������

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(gatewayId);

	if (logic_readVersion(gatewayId, hardVersion, softVersion) == ERROR) {
		GUI_MessageBox("\n��ѯ�汾ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	}
	else {
		hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
		EDIT_SetText(hItem, (char*)softVersion);
		hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT2);
		EDIT_SetText(hItem, (char*)hardVersion);
	}
	WM_SetFocus(hDlg);
}

void queryVersionCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		queryVersionInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://��ѯ�汾
				userQueryVersion(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://��ѯ�汾
			userQueryVersion(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userReadBaseinfo(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	db_meterinfo_str dbBaseInfoStr = { 0 };

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	supplementTo12(gatewayId);

	if (logic_readBaseInfo(gatewayId, &dbBaseInfoStr) == ERROR) {
		GUI_MessageBox("\n��ȡ����ַʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROWID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.rowId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERADDR);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.meterAddr);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VENDORID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.vendorId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_PROTOVER);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.protoVer);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERTYPE);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.meterType);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CHANNEL);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.channel);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEPROTOVER);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.valveProtoVer);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEADDR);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.valveAddr);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CONTROLPANELADDR);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.controlPanelAddr);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_BUILDID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.buildId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_UNITID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.unitId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROOMID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.roomId);
	}
	WM_SetFocus(hDlg);
}

void userReadNextBaseinfo(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	db_meterinfo_str dbBaseInfoStr = { 0 };
	if (logic_readNextTempInfo(&dbBaseInfoStr) == ERROR) {
		GUI_MessageBox("\n��ȡ��һ��ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
	}
	else {
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROWID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.rowId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERADDR);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.meterAddr);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VENDORID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.vendorId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_PROTOVER);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.protoVer);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_METERTYPE);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.meterType);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CHANNEL);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.channel);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEPROTOVER);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.valveProtoVer);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_VALVEADDR);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.valveAddr);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_CONTROLPANELADDR);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.controlPanelAddr);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_BUILDID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.buildId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_UNITID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.unitId);
		hItem = WM_GetDialogItem(hDlg, EDIT_MODIFY_1INFO_ROOMID);
		EDIT_SetText(hItem, (const char*)dbBaseInfoStr.roomId);
	}
}

void userUpdateDbf(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
		return;
	}
	supplementTo12(gatewayId);
	if (logic_updateBaseInfo(gatewayId) == ERROR) {
		GUI_MessageBox("\n���±���ַʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		GUI_MessageBox("\n���±���ַ�ɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void ReadBaseInfoCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		queryBaseInfoInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://��ȡ������Ϣ
				userReadBaseinfo(hDlg);
				break;
			case GUI_ID_BUTTON2://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON3://��һ��
				userReadNextBaseinfo(hDlg);
				break;
			case GUI_ID_BUTTON4:
				userUpdateDbf(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM2://��ȡ������Ϣ
			userReadBaseinfo(hDlg);
			break;
		case GUI_KEY_NUM3://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM4://��һ��
			userReadNextBaseinfo(hDlg);
			break;
		case GUI_KEY_NUM5:
			userUpdateDbf(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userReadAllHisData(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8	cntStr[10] = { 0 };
	float percent = 0.0;

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n����������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	supplementTo12(gatewayId);
	gu16sucCnt = gu16failCnt = 0;
	if (logic_readHisData(gatewayId, &gu16sucCnt, &gu16failCnt) == ERROR) {
		GUI_MessageBox("\n��ȡ��ʷ����ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
	} else {
		Lib_sprintf((char*)cntStr, "%d", gu16sucCnt);
		hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
		EDIT_SetText(hItem, (const char*)cntStr);

		Lib_sprintf((char*)cntStr, "%d", gu16failCnt);
		hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT2);
		EDIT_SetText(hItem, (const char*)cntStr);

		if ((gu16sucCnt + gu16failCnt) == 0) {
			percent = 0.0;
		} else {
			percent = (gu16sucCnt * 100 / (gu16sucCnt + gu16failCnt));
		}

		Lib_sprintf((char*)cntStr, "%.01f%%", percent);//������С��λ, ԭ����
		hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT3);
		EDIT_SetText(hItem, (const char*)cntStr);
		gu8hasReadHisData = NO_ERR;
		//GUI_MessageBox("\n��ȡ��ʷ���ݳɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
}

void userReadNextHisData(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	db_hisdata_str dbHisStr = { 0 };
	if (logic_nextHisData(&dbHisStr, gu8success) == ERROR) {
		GUI_MessageBox("\n��ȡ��һ������ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
	} else {
		hItem = WM_GetDialogItem(hDlg, GUI_ID_LISTVIEW0);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_id, (const char*)dbHisStr.id);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_maddr, (const char*)dbHisStr.maddr);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_build, (const char*)dbHisStr.build);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_unit, (const char*)dbHisStr.unit);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_room, (const char*)dbHisStr.room);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_intemp, (const char*)dbHisStr.intemp);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_outtemp, (const char*)dbHisStr.outtemp);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_flow, (const char*)dbHisStr.flow);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_heat, (const char*)dbHisStr.heat);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_roomtemp, (const char*)dbHisStr.roomtemp);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_vopen, (const char*)dbHisStr.vopen);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_fsuc, (const char*)dbHisStr.fsuc);
	}
}

void hisSheetCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		hisSheetInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON1://��һ��
				userReadNextHisData(hDlg);
				break;
			case GUI_ID_BUTTON4:
				userUpdateDbf(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM2://��һ��
			userReadNextHisData(hDlg);
			break;
		case GUI_KEY_NUM5:
			userUpdateDbf(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userReadHisSheet(U8 suc)
{
	int iRet;

	if (gu8hasReadHisData == ERROR) {
		GUI_MessageBox("\n���ȶ�ȡ��ʷ����\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}
	gu8success = suc;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetHisSheet, GUI_COUNTOF(widgetHisSheet), &hisSheetCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void queryHisDataCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		queryHisDataInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://��ȡ��ʷ����
				userReadAllHisData(hDlg);
				break;
			case GUI_ID_BUTTON3://�ɹ��굥
				userReadHisSheet(NO_ERR);
				break;
			case GUI_ID_BUTTON4://ʧ���굥
				userReadHisSheet(ERROR);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://��ȡ��ʷ����
			userReadAllHisData(hDlg);
			break;
		case GUI_KEY_NUM4://�ɹ��굥
			userReadHisSheet(NO_ERR);
			break;
		case GUI_KEY_NUM5://ʧ���굥
			userReadHisSheet(ERROR);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void userRemote1Meter(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	db_hisdata_str dbHisStr = { 0 };
	U8 gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8	idStr[10] = { 0 };

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n���ڼ�������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	supplementTo12(gatewayId);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_GetText(hItem, (char*)idStr, 5);
	if (isNumber(idStr, STRLEN(idStr)) == ERROR) {
		GUI_MessageBox("\n���ڼ�������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		return;
	}

	if (logic_remoteOneMeterId(gatewayId, idStr, &dbHisStr) == ERROR) {
		GUI_MessageBox("\n͸��ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
	} else {
		hItem = WM_GetDialogItem(hDlg, GUI_ID_LISTVIEW0);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_id, (const char*)dbHisStr.id);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_maddr, (const char*)dbHisStr.maddr);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_build, (const char*)dbHisStr.build);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_unit, (const char*)dbHisStr.unit);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_room, (const char*)dbHisStr.room);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_intemp, (const char*)dbHisStr.intemp);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_outtemp, (const char*)dbHisStr.outtemp);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_flow, (const char*)dbHisStr.flow);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_heat, (const char*)dbHisStr.heat);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_roomtemp, (const char*)dbHisStr.roomtemp);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_vopen, (const char*)dbHisStr.vopen);
		LISTVIEW_SetItemText(hItem, LISTVIEW_COL_VALUE, em_filedidx_fsuc, (const char*)dbHisStr.fsuc);
	}
}
void remote1MeterCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;

	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		remote1MeterInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON0://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON1://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON2://͸����������������
				userRemote1Meter(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM1://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM2://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM3://͸����������������
			userRemote1Meter(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

U8 getUartMode(em_databit_idx data, em_parity_idx parity, em_stop_idx stop)
{
	U8 i = 0;
	U8	modeCnt = sizeof(gUart_mode_strMap) / sizeof(uart_mode_str);
	for (i = 0; i < modeCnt;i++) {
		if (gUart_mode_strMap[i].databit == data  &&\
			gUart_mode_strMap[i].parity == parity &&\
			gUart_mode_strMap[i].stop == stop) {
			return (i + 1);
		}
	}
	return ERROR;
}

void userSaveConfig(WM_HWIN hDlg)
{
	WM_HWIN hItem;
	U8  device;
	U32 baud;
	em_databit_idx	data;
	em_parity_idx	parity;
	em_stop_idx		stop;
	U8  mode;
	U8	gatewayId[2 * GATEWAY_OADD_LEN + 1] = { 0 };
	U8	svrId[2 * GATEWAY_SADD_LEN + 1] = { 0 };
	

	//�豸
	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN0);
	device = gu8deviceIntArray[DROPDOWN_GetSel(hItem)];
	//������
	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN1);
	baud = gu32baudIntArray[DROPDOWN_GetSel(hItem)];
	//����λ
	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN2);
	data = (em_databit_idx)DROPDOWN_GetSel(hItem);
	//У��λ
	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN3);
	parity = (em_parity_idx)DROPDOWN_GetSel(hItem);
	//ֹͣλ
	hItem = WM_GetDialogItem(hDlg, GUI_ID_DROPDOWN4);
	stop = (em_stop_idx)DROPDOWN_GetSel(hItem);
	mode = getUartMode(data, parity, stop);
	if (mode == ERROR) {
		GUI_MessageBox("\n�˴������ñ�ϵͳ��֧��\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hDlg);
		return;
	}

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0);
	EDIT_GetText(hItem, (char*)gatewayId, 2 * GATEWAY_OADD_LEN);
	if (isNumber(gatewayId, STRLEN(gatewayId)) == ERROR) {
		GUI_MessageBox("\n���ڼ�������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	supplementTo12(gatewayId);

	hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT1);
	EDIT_GetText(hItem, (char*)svrId, 2 * GATEWAY_SADD_LEN);
	if (isNumber(svrId, STRLEN(svrId)) == ERROR) {
		GUI_MessageBox("\n���ڼ�������������\n", "����", GUI_MESSAGEBOX_CF_MODAL);
		WM_SetFocus(hItem);
		return;
	}
	supplementTo12(svrId);

	if (logic_saveConfig(device, baud, mode, gatewayId, svrId)==ERROR) {
		GUI_MessageBox("\n��������ʧ��\n", "ʧ��", GUI_MESSAGEBOX_CF_MODAL);
	} else {
		GUI_MessageBox("\n�������óɹ�\n", "�ɹ�", GUI_MESSAGEBOX_CF_MODAL);
	}
	WM_SetFocus(hDlg);
}

void deviceConfigCb(WM_MESSAGE* pMsg)
{
	int NCode, Id;
	WM_HWIN hDlg;
	hDlg = pMsg->hWin;

	switch (pMsg->MsgId)
	{
	case WM_INIT_DIALOG:
		deviceConfigInit(hDlg);
		break;
	case WM_PAINT:
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (NCode)
		{
		case WM_NOTIFICATION_RELEASED: //��������Ϣ
			switch (Id) {
			case GUI_ID_BUTTON5://�㲥����������
				radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
				break;
			case GUI_ID_BUTTON0://�˳�
				GUI_EndDialog(hDlg, WM_USER_EXIT);
				break;
			case GUI_ID_BUTTON1://��������
				userSaveConfig(hDlg);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEY: //������Ϣ
		switch (((WM_KEY_INFO *)(pMsg->Data.p))->Key) {
		case GUI_KEY_ESCAPE://Exit
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM6://�㲥����������
			radioReadGatewayId(WM_GetDialogItem(hDlg, GUI_ID_EDIT0));
			break;
		case GUI_KEY_NUM1://�˳�
			GUI_EndDialog(hDlg, WM_USER_EXIT);
			break;
		case GUI_KEY_NUM2://��������
			userSaveConfig(hDlg);
			break;
		case GUI_KEY_ENTER:
			break;
		case GUI_KEY_UP:
			WM_SetFocusOnPrevChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		case GUI_KEY_DOWN:
			WM_SetFocusOnNextChild(WM_GetParent(WM_GetDialogItem(hDlg, GUI_ID_BUTTON0)));
			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/************************************************************************/
/* �������溯��Ⱥ                                                       */
/************************************************************************/
void setTimeConfig()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetSetTime, GUI_COUNTOF(widgetSetTime), &setTimeCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void baseinfoIssue()
{
    int iRet;
    while(1){
        iRet = GUI_ExecDialogBox(widgetBaseInfoIssue, GUI_COUNTOF(widgetBaseInfoIssue), &baseInfoIssueCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
    }
}

void modifyOneInfo()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetModifyMeterInfo, GUI_COUNTOF(widgetModifyMeterInfo), &modifyOneInfoCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void setTimeNodes()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetTimeNodes, GUI_COUNTOF(widgetTimeNodes), &setTimeNodesCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void modifyGatewayId()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetModifyGatewayId, GUI_COUNTOF(widgetModifyGatewayId), &modifyGatewayIdCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void modifyGPRS()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetModifyGPRS, GUI_COUNTOF(widgetModifyGPRS), &modifyGPRSCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void reboot()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetReboot, GUI_COUNTOF(widgetReboot), &rebootCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void rereadParam()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetRereadParam, GUI_COUNTOF(widgetRereadParam), &rereadCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

int dispConfig(){
    int iRet;
    while(1){
        iRet = GUI_ExecDialogBox(widgetSetParaAndControl, GUI_COUNTOF(widgetSetParaAndControl), &setParaAndControlCb, WM_HBKWIN, 0, 0);
        switch(iRet){
        case GUI_ID_BUTTON0://Уʱ
			setTimeConfig();
            break;
        case GUI_ID_BUTTON1://������ʱ
			setTimeNodes();
            break;
        case GUI_ID_BUTTON2://�޸ļ�������
			modifyGatewayId();
            break;
        case GUI_ID_BUTTON3://GPRS����
			modifyGPRS();
            break;
        case GUI_ID_BUTTON4://��������
			rereadParam();
            break;
        case GUI_ID_BUTTON5://������Ϣ�·�
            baseinfoIssue();
            break;
        case GUI_ID_BUTTON6://������Ϣ�޸�
			modifyOneInfo();
            break;
        case GUI_ID_BUTTON7://����������
			reboot();
            break;
        case 0:
            return 0;
        case -1:
            return -1;
        default:
			break;
        }
    }
}

void readMeterImmd()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetReadMeterImmd, GUI_COUNTOF(widgetReadMeterImmd), &readMeterImmdCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void queryVersion()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetQueryVersion, GUI_COUNTOF(widgetQueryVersion), &queryVersionCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void queryBaseInfo()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetReadBaseInfo, GUI_COUNTOF(widgetReadBaseInfo), &ReadBaseInfoCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

void queryHisData()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetHisData, GUI_COUNTOF(widgetHisData), &queryHisDataCb, WM_HBKWIN, 0, 0);

		switch (iRet) {
		case GUI_ID_BUTTON3://�ɹ��굥
			break;
		case GUI_ID_BUTTON4://ʧ���굥
			break;
		case WM_USER_EXIT:
			return;
		default:
			break;
		}
	}
}

void remoteOneMeter()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetRemote1Meter, GUI_COUNTOF(widgetRemote1Meter), &remote1MeterCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return;
	}
}

int queryEditInfo()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetQueryEditInfo, GUI_COUNTOF(widgetQueryEditInfo), &queryEditInfoCb, WM_HBKWIN, 0, 0);
		switch (iRet) {
		case GUI_ID_BUTTON0://��������
			readMeterImmd();
			break;
		case GUI_ID_BUTTON1://��ѯ��ʷ����
			queryHisData();
			break;
		case GUI_ID_BUTTON2://��ȡ����Ϣ
			queryBaseInfo();
			break;
		case GUI_ID_BUTTON3://͸��һ�������������
			remoteOneMeter();
			break;
		case GUI_ID_BUTTON4://��Ӳ���汾��ѯ
			queryVersion();
			break;
		case 0:
			return 0;
		case -1:
			return -1;
		default:
			break;
		}
	}
}

int deviceConfig()
{
	int iRet;
	while (1) {
		iRet = GUI_ExecDialogBox(widgetDeviceConfig, GUI_COUNTOF(widgetDeviceConfig), &deviceConfigCb, WM_HBKWIN, 0, 0);
		if (iRet == WM_USER_EXIT)
			return WM_USER_EXIT;
	}
}

int maingui( void ){
    int iRet;

	while (1) {
        iRet=GUI_ExecDialogBox(widgetMainFrame, GUI_COUNTOF(widgetMainFrame), &mainCb, WM_HBKWIN, 0, 0);//������ִ�жԻ���
        switch(iRet){
        case GUI_ID_BUTTON0:
            dispConfig();
			break;
        case GUI_ID_BUTTON1:
			queryEditInfo();
			break;
        case GUI_ID_BUTTON2:
			deviceConfig();
			break;
        case -1:
            return -1;
        default:
			break;
        }
    }
}
