//
// Created by zhouhaibo on 2017/9/21.
//

#include "parse_config.h"

#define LOG_TAG "ParseConfig"

void parsingFilterConfig(ConstString filterZipPath, FilterConfig *filterConfig) {
    if (NULL == filterZipPath || NULL == filterConfig) {
        return ;
    }

    int length = strlen(filterZipPath) + strlen("/config");
    char *tmpPath = (char *)malloc( length + 1);
    memset(tmpPath, '\0', length + 1);
    memcpy(tmpPath, filterZipPath, strlen(filterZipPath));
    char *filename = strcat(tmpPath, "/config");

    FILE *fp = NULL;
    fp = fopen(filename, "rb");
    if (NULL == fp) {
        LOGE(LOG_TAG, "open bin file failed, bin file name: %s", filename);
        return ;
    }
    // 两字节头信息, 一字节type 一字节num
    uint8_t type = 0;
    uint8_t num = 0;

    uint8_t head[2] = {0};
    size_t  headSize = fread(head, 1, sizeof(head), fp);
    if (headSize != sizeof(head)) {
        LOGE(LOG_TAG, "read bin head failed, read numSize: %d", headSize);
        fclose(fp);
        return ;
    }

    type = head[0];
    num = head[1];

    if (type <= 0) {
        filterConfig->type = 0;
        filterConfig->num = 0;
        filterConfig->data = NULL;
        return;
    }

    // 设置type类型
    filterConfig->type = type;

    if (num <= 0) {
        filterConfig->num = 0;
        filterConfig->data = NULL;
        return;
    }

    // 设置num数量
    filterConfig->num = num;
    filterConfig->data = new FilterData[num];

    // 读取num个数据配置
    for (int i = 0; i < num ; i ++) {
        // 1字节type + 64字节名称
        uint8_t type = 0;
        fread(&type, 1, 1, fp);
        if (type == 1) {
            filterConfig->data[i].type = Type_Bin_Data;
        } else if (type == 2) {
            filterConfig->data[i].type = Type_Png_Data;
        } else {
            filterConfig->data[i].type = Type_None;
        }

        memset(filterConfig->data[i].name, '\0', sizeof(filterConfig->data[i].name));
        char name[64] = {'\0'};
        fread(name, 1, 64, fp);

        memcpy(filterConfig->data[i].name, filterZipPath, strlen(filterZipPath));
        filterConfig->data[i].name[strlen(filterZipPath)] = '/';
        memcpy(filterConfig->data[i].name + strlen(filterZipPath) + 1, name, sizeof(name));
    }
}