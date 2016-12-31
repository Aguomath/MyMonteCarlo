#include"header.h"
/*
 *   函数过于短小，不适合大规模程序
 *   数据结构设计不太理想，还是得再认真想清楚再进行设计
 *   刚开始功能不必过于复杂，需要简化问题
 *   没有把所学到的知识应用到代码开发中去，
 *   要认真考虑为什么出现这样的错误
 *   2016年12月31日     今年的最后一天，在写代码中度过
 *
 */

void FInitCell(struct CELL * tmp)
{
    tmp->_id = 0;
// tmp->_name = (char*)"";
    tmp->_mat = NULL;
    tmp->_facelist = NULL;
    return ;
}

void FInitCellList(struct CELLLIST *tmp)
{
    FInitCell(&(tmp->_cell));
    tmp->_next = NULL;
    return;
}


struct CELLLIST * FNewCell()
{
    struct CELLLIST *tmp;
    if(gcelllist == NULL ){
        tmp = (struct CELLLIST*)
            malloc(sizeof(struct CELLLIST));

        gcelllist = tmp;

        FInitCellList(tmp);
        return tmp;
    }
    else{
        tmp = gcelllist;
        while(tmp->_next != NULL)
            tmp = tmp->_next;
        tmp->_next = (struct CELLLIST*)
            malloc(sizeof(struct CELLLIST));
        FInitCellList(tmp->_next);
        return tmp->_next;
    }
    return NULL;
}


struct MATERIAL * FNewMaterial()
{
    struct MATERIAL * tmp = 
        (struct MATERIAL*)
        malloc(sizeof(struct MATERIAL));

    tmp->_matid = MININF;
    return tmp;
}


struct FACELIST * FNewFaceList()
{
    struct FACELIST * tmp = 
        (struct FACELIST*)malloc(sizeof(struct FACELIST));

    tmp->_next = NULL;
    tmp->_face = NULL;

    return tmp;

}

struct GFACE * FNewGface()
{
  struct GFACE *tmp;
  if(gface == NULL){
      tmp = (struct GFACE*)malloc(sizeof(struct GFACE));
      gface = tmp;
      tmp->_next = NULL;
      return tmp;
    }
  else{
      tmp = gface;
      while(tmp->_next != NULL)
          tmp = tmp->_next;
      tmp->_next = (struct GFACE*)
          malloc(sizeof(struct GFACE));
      //FInitCellList(tmp->_next);
      tmp->_next->_next = NULL;
      return tmp->_next;
    }

}


















