/*
*
*   - Author: jrius ( vk.com/s.fridom | t.me/dcapybarov ) -
*   - Include: format-string
*   - ������ ���������� �� ������ ����������� 3.10.8 -
*
*   - ������ ������������� ��������� �������:
*  
*       * ShowStaticDialog(playerid, dialog_name[] = "test")
*           - playerid - ���� ������� ������ [!] ������������ ��������
*           - dialog_name - ������, ������� ������ � xml ����� [!] ������������ ��������
*
*
*   - ��� ������� ����, ������� ����� �������� ��� ��������?
*       [1] � �������� (�����) scriptfiles ������� ��� ���� ������� � ��������� xmls (��� ������� ��� ��������, ����� � �������� �� ���� 100500 ������)
*       [2] ������� ���� � ����������� xml, � PATH_DIALOG_XMLS �������: �������� ��������/�������� �����.���������� - ������� dialogs.xml
*       [3] � ����� ���� ������� ������� ������ �������
*/

#include <xml>

#if !defined str_d
    new str_format_buffer[4096];

    #define str_d(%0,%1) str_format_buffer[0] = EOS, format(str_format_buffer, sizeof str_format_buffer, %0, %1), str_format_buffer 
#endif

new PATH_DIALOG_XMLS[] = "xmls/dialogs.xml";

stock ShowStaticDialog(playerid, dialog_name[])
{
    new XML:xml = xml_open(PATH_DIALOG_XMLS);

    if (xml)
    {
        new DialogId, StyleId, 
            caption[144], Text[1024], 
            Button_1[32], Button_2[32];

        format(string_global, sizeof string_global, "/dialogs/dialog[@name='%s']/dialogId", dialog_name);
        DialogId = xml_get_int(xml, string_global);

        format(string_global, sizeof string_global, "/dialogs/dialog[@name='%s']/styleId", dialog_name);
        StyleId = xml_get_int(xml, string_global); 

        xml_get_string(xml, (str_d("/dialogs/dialog[@name='%s']/caption", dialog_name)), caption);
        xml_get_string(xml, (str_d("/dialogs/dialog[@name='%s']/text", dialog_name)), Text);

        xml_get_string(xml, (str_d("/dialogs/dialog[@name='%s']/button1", dialog_name)), Button_1);
        xml_get_string(xml, (str_d("/dialogs/dialog[@name='%s']/button2", dialog_name)), Button_2);

        if (TestServer) printf("[ShowStaticDialog] ShowPlayer: %d \
            | DialogId: %d \
            | DialogStyle: %d \
            | DialogCaption: %s \
            | DialogText: %s \
            | DialogButton1: %s \
            | DialogButton2: %s \
            | DialogName: %s",
        playerid, DialogId, StyleId, caption, Text, Button_1, Button_2, dialog_name);

        ShowPlayerDialog(playerid, DialogId, StyleId, caption, Text, Button_1, Button_2);
        return 1;
    }
    else 
    {
        SendError(playerid, "[ShowStaticDialog] xml file not open.");
        return 0;
    }
}

/*

������ ������� � xml �������:

<dialog name=""> - ��� � ������� dialog_name
��������� �� ������� 

ID,
Style,
Caption,
Info,
Button1,
Button2

<?xml version="1.0"?>
<dialogs>
    <dialog name="test"> 
        <dialogId>0</dialogId> <styleId>123123</styleId>
        
        <caption>����</caption>
        <text>Test2</text>

        <button1>button1</button1> <button2>button2</button2>
    </dialog>
</dialogs>


*/