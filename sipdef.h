#pragma once

enum CommandCode
{
    Command_Session_Register=1,
    Command_Session_Catalog=2,
    Command_Session_RealPlay=3,
};

//类型编码枚举 11 12 13位
enum DevTypeCode
{
    Error_Code=-1,
    Dvr_Code= 111,
    ViderServer_Code=112,//视频服务器
    Encoder_Code=113,//编码
    Decoder_Code=114,//解码
    AlarmDev_Code=117,//报警控制器编码
    NVR_Code=118,//网络视频录像机

    Camera_Code=131,//USB摄像头
    Ipc_Code=132,//网络摄像头
    VGA_Code=133,//显示器
    AlarmInput_Code=134,//报警设备
    AlarmOutput_Code=135,//报警输出设备

    CenterServer_Code=200, //中心信令控制服务器编码
};