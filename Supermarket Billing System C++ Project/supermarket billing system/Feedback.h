#ifndef _FEEDBACK_H_
#define _FEEDBACK_H_

#include "mainHeader.h"

class Feedback {
private:
    char phone[11];
    char name[26];
    char feedback[101];
public:
    void addFeedback();
    void showFeedback();
    void removeFeedback();
    char* returnPhone();
} fbk;

#endif