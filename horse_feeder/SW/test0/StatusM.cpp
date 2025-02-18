#include "StatusM.h"


StatusM::StatusM(DateTime now){
	for(uint8_t i=0;i<ERRORTypeNB;i++){
		err_cnt[err]=EEPROM.read(EEPROM_STATUS_ADDR + i);
	}
	startupTime=((now.year-2025)*365+now.month*31+now.day)*24+now.hours;
}
void StatusM:getReport(char *text_content){
	uint16_t uptime=((nowTime.year-2025)*365+nowTime.month*31+nowTime.day)*24+nowTime.hours;
	uptime-=startupTime;
	
	text_length += sprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("SIM SW restart: %u, Mot:%u/%u/%u, RTC: %u, "), err_cnt[SIM_ERROR], err_cnt[M1_ERROR], err_cnt[M2_ERROR], err_cnt[M12_ERROR], err_cnt[RTC_ERROR]);
	text_length += sprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("%ud,%uh"), uptime/24, uptime%24);
	text_length += sprintf_P(text_content + text_length, SMS_TEXT_BUF - text_length, PSTR("%d/%d/%d, %dh%02d"), d.day, d.month, d.year, d.hours, d.minutes);
}

void StatusM::resetStats(){
	for(uint8_t i=0;i<ERRORTypeNB;i++){
		err_cnt[err]=0;
		EEPROM.update(EEPROM_STATUS_ADDR + err, 0);
	}
}

void StatusM::update(DateTime now){
	nowTime=now;
	batt_level=(batt_level*15+(analogRead(BATT_MON)*BATT_ADC_GAIN))>>4;
}
void StatusM::increaseErrorCnt(ErrorType err){
	err_cnt[err]++;
    EEPROM.update(EEPROM_STATUS_ADDR + err, err_cnt[err]);
}