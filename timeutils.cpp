#include "timeutils.h"

#include <QDateTime>
#include <chrono>

TimeUtils::TimeUtils()
{

}

unsigned long long TimeUtils::getCurrentNanoSinceEpoch()
{
    using namespace std::chrono;
    return duration_cast<nanoseconds>(
               system_clock::now().time_since_epoch()).count();
}

QString TimeUtils::getCurrentTimeFormatted()
{
    auto now = QDateTime::currentDateTime();
    int year = now.date().year();
    int month = now.date().month();
    int day = now.date().day();
    int hour = now.time().hour();
    int minute = now.time().minute();
    int second = now.time().second();

    timestamp_t timestamp = getCurrentNanoSinceEpoch();
    timestamp_t nanosecond = timestamp % 1000;
    timestamp /= 1000;
    timestamp_t microsecond = timestamp % 1000;
    timestamp /= 1000;
    timestamp_t millisecond = timestamp % 1000;

    return QString("%1年%2月%3日 %4时%5分%6秒 %7毫秒%8微秒%9纳秒")
            .arg(year)
            .arg(month)
            .arg(day)
            .arg(hour)
            .arg(minute)
            .arg(second)
            .arg(millisecond)
            .arg(microsecond)
            .arg(nanosecond);
}
