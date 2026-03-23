#ifndef INC_UNI_NLU_CONTENT_H_
#define INC_UNI_NLU_CONTENT_H_

typedef struct {
  uni_u32 key_word_hash_code; /* 存放识别词汇对应的hashcode */
  uni_u8  nlu_content_str_index; /* 存放nlu映射表中的索引，实现多个识别词汇可对应同一个nlu，暂支持256条，如果不够换u16 */
  char    *hash_collision_orginal_str /* 类似Java String equal，当hash发生碰撞时，赋值为识别词汇，否则设置为NULL */;
} uni_nlu_content_mapping_t;

enum {
  eCMD_wakeup_uni,
  eCMD_exitUni,
  eCMD_TurnOn,
  eCMD_why,
  eCMD_shit,
  eCMD_name,
};

const char* const g_nlu_content_str[] = {
[eCMD_wakeup_uni] = "{\"asr\":\"巴嘎王子\",\"cmd\":\"wakeup_uni\",\"pcm\":\"[103]\"}",
[eCMD_exitUni] = "{\"asr\":\"再见\",\"cmd\":\"exitUni\",\"pcm\":\"[104]\"}",
[eCMD_TurnOn] = "{\"asr\":\"你叫什么\",\"cmd\":\"TurnOn\",\"pcm\":\"[105]\"}",
[eCMD_why] = "{\"asr\":\"为什么叫哈达\",\"cmd\":\"why\",\"pcm\":\"[106]\"}",
[eCMD_shit] = "{\"asr\":\"你吃屎吗\",\"cmd\":\"shit\",\"pcm\":\"[107]\"}",
[eCMD_name] = "{\"asr\":\"巴嘎\",\"cmd\":\"name\",\"pcm\":\"[108]\"}",
};

/*TODO perf sort by hashcode O(logN), now version O(N)*/
const uni_nlu_content_mapping_t g_nlu_content_mapping[] = {
  {1307193309U/*巴嘎王子*/, eCMD_wakeup_uni, NULL},
  {2389288886U/*再见*/, eCMD_exitUni, NULL},
  {39361668U/*你叫什么*/, eCMD_TurnOn, NULL},
  {4250429375U/*为什么叫哈达*/, eCMD_why, NULL},
  {661573851U/*你吃屎吗*/, eCMD_shit, NULL},
  {2435699929U/*巴嘎*/, eCMD_name, NULL},
};

#endif
