#pragma once

typedef int Data;

struct ListNode {
  Data info;
  ListNode *next;
};

ListNode *subset(ListNode *list, Data m);
