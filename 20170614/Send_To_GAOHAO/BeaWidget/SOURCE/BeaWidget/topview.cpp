#include "topview.h"
#include "ui_topview.h"
#include <QGraphicsItemAnimation>
#include <QDebug>
#include <QMenu>
#include <QMessageBox>
#include <QTextCodec>
#include <QSqlQuery>
#include <QListWidgetItem>
#include "addswitchdialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include "addline.h"
#include "connection.h"
#include "switchstateview.h"

TopView::TopView(QWidget *parent)
    : QGraphicsView(parent),ui(new Ui::TopView)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->scene->setFixedSize(this->width(),this->height());
    m_select_item = NULL;   //yangmeng 161021 指针初始化为NULL，防止析构出错
    m_moving_item = NULL;
    is_press=false;
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QFont font_t("Times",16);
    scene = new QGraphicsScene(this);

    scene->setSceneRect(-ui->scene->width()/2,
                        -ui->scene->height()/2,
                        ui->scene->width(),
                        ui->scene->height());

    //old set
//    normalswitchpix=QPixmap(":/img/switch/normalswitch");
//    warningswitchpix =QPixmap(":/img/switch/warningswitch");
//    breakswitchpix=QPixmap(":/img/switch/downswitch");      //*1
//    normalswitchpix_core=QPixmap(":/img/switch/switch_core");//*2
//    warningswitchpix_core =QPixmap(":/img/switch/switch_core_warning");//*3
//    breakswitchpix_core=QPixmap(":/img/switch/switch_core_break");//*4

    //Shang new set
    //[1]
    normalswitchpix = QPixmap(":/newswitch/newswitch/switch_normal");
    warningswitchpix = QPixmap(":/newswitch/newswitch/switch_warning");
    breakswitchpix = QPixmap(":/newswitch/newswitch/switch_break");                   //*1
    normalswitchpix_core = QPixmap(":/newswitch/newswitch/switch_core_normal");       //*2
    warningswitchpix_core = QPixmap(":/newswitch/newswitch/switch_core_warning");    //*3
    breakswitchpix_core = QPixmap(":/newswitch/newswitch/switch_core_break");         //*4

    int w = qApp->desktop()->screen()->width();
    int h = qApp->desktop()->screen()->height();
    QSize size(w*0.04,h*0.5);
    normalswitchpix = normalswitchpix.scaled(size,Qt::KeepAspectRatio);
    warningswitchpix = warningswitchpix.scaled(size,Qt::KeepAspectRatio);
    breakswitchpix = breakswitchpix.scaled(size,Qt::KeepAspectRatio);
    normalswitchpix_core = normalswitchpix_core.scaled(size,Qt::KeepAspectRatio);
    warningswitchpix_core = warningswitchpix_core.scaled(size,Qt::KeepAspectRatio);
    breakswitchpix_core = breakswitchpix_core.scaled(size,Qt::KeepAspectRatio);
    //~[1]

    ui->scene->setScene(scene);

    slot_init();

    connect (scene,SIGNAL(selectionChanged()),this,SLOT(slot_SeletedSwitchNumber()));
    connect(this,SIGNAL(signal_moving(QPoint)),this,SLOT(slot_moving(QPoint)));

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff) ;
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff ) ;
//    setBackgroundBrush(QBrush(QColor(178,200,187)));

}

void TopView::slot_init()
{
    // 清空之前的拓扑信息
    for (int i=0;i<m_all_line.size();i++)
     {
         QGraphicsLineItem *ql=m_all_line.at(i);
         if(ql)
             delete ql;
     }
     QMap<QString,Switcher*>::iterator it;
     for ( it = m_switch_map.begin(); it != m_switch_map.end();  ) {
         Switcher * line_swi=it.value();
         if(line_swi)
         delete line_swi;
     }
     QMap<QString,int*>::iterator itp;
     for ( itp = portsState.begin(); itp != portsState.end();  ) {
         int * pp=itp.value();
         if(pp)
         delete[] pp;
     }
     //QFont font_t("Times",16);
    //QFont font_t("Lohit Tamil",14);    //yangmeng 161026 调整拓扑图字体
     QFont font_t("Lohit Gujarati",14);    //yangmeng 161026 调整拓扑图字体
    m_switch_map.clear();
    m_all_line.clear();
    m_all_line_pos.clear();
    portsState.clear();
    scene->clear();
    //重新从数据库查询拓扑信息
    QSqlQuery query("",DBConnection::db);;
    query.prepare("select  switch_topo.name,switch_topo.ip,switch_topo.community,pos_x,pos_y,remark from switch_topo,switch  where switch_topo.name=switch.name");
    query.exec();
    //绘制交换机图标信息
    while(query.next())
    {
         Switcher *swi=new Switcher();
         swi->setName(query.value(0).toString());
         swi->setIp(query.value(1).toString());
         swi->setComunity(query.value(2).toString());
         swi->setPos(query.value(3).toFloat(),query.value(4).toFloat());
         swi->setType(query.value(5).toString());

         QPointF picturecenter(normalswitchpix.width()/2,normalswitchpix.height()/2);
         MyGraphicsPixmapItem *pix=new MyGraphicsPixmapItem();
         QString pix_name=swi->getName();
         pix->setPixName(pix_name);
         if(pix_name=="H1"||pix_name=="H2")
              pix->setPixmap(normalswitchpix_core);
         else pix->setPixmap(normalswitchpix);
         pix->setFlag(QGraphicsItem::ItemIsSelectable);
         pix->setPos(swi->getPos()-picturecenter);
         scene->addItem(pix);
         swi->pix=pix;

         swi->text = new QGraphicsTextItem(swi->getName());
         swi->text->setFont(font_t);
         swi->text->setDefaultTextColor(QColor(255,255,255));
         //swi->text->setPos(swi->getPos().x()-picturecenter.x(),swi->getPos().y()+5+normalswitchpix.height()-picturecenter.y());     //yangmeng 调整拓扑图文字位置
         swi->text->setPos(swi->getPos().x()-picturecenter.x()+5,
                           swi->getPos().y()-picturecenter.y()+normalswitchpix.height());     //yangmeng 调整拓扑图文字位置


         scene->addItem(swi->text);

         m_switch_map.insert(swi->getName(),swi);
    }
    //根据数据库中的信息绘制交换机连线
    query.prepare("select  pos_x1,pos_y1,pos_x2,pos_y2, switch_name1,switch_name2 from switch_line");
    query.exec();
    while(query.next())
    {
        QPen linepen(QBrush(QColor(114,111,128)),2,Qt::DashLine);

        QGraphicsLineItem *line=scene->addLine(query.value(0).toFloat(),
                                               query.value(1).toFloat(),
                                               query.value(2).toFloat(),
                                               query.value(3).toFloat(),
                                               linepen);
        line->setZValue (-1);
        m_switch_map[query.value(4).toString()]->p_line_list.append(line);
        m_switch_map[query.value(4).toString()]->obj_swi_name_list<<query.value(5).toString();
        m_switch_map[query.value(5).toString()]->p_line_list.append(line);
        m_switch_map[query.value(5).toString()]->obj_swi_name_list<<query.value(4).toString();

        m_all_line.append(line);
        QList<QString> line_pos_t;
        line_pos_t<<query.value(4).toString()<<query.value(5).toString();
        m_all_line_pos<<line_pos_t;
    }
    //交换机实际链接信息
    query.prepare("select name,port,objname,objport from switch_conn");
    query.exec();
    while(query.next())
    {
        m_switch_port_map.insert(query.value(0).toString()+"-"+QString::number(query.value(1).toInt()-1),
                                 query.value(2).toString()+"-"+QString::number(query.value(3).toInt()-1));
    }
    query.finish();
    query.clear();
}

void TopView::slot_setAlarmSwitch(QString switchName,QString alarmType,QString value)
{
    if(switchName=="H1"||switchName=="H2")
    {
        if(alarmType=="交换机不可达"){
             m_switch_map[switchName]->pix->setPixmap(breakswitchpix_core);
        }
        else {
             m_switch_map[switchName]->pix->setPixmap(warningswitchpix_core);
        }
    }
    else
    {
         if(alarmType=="交换机不可达"){
             m_switch_map[switchName]->pix->setPixmap(breakswitchpix);
         }
         else{
              m_switch_map[switchName]->pix->setPixmap(warningswitchpix);
         }
    }

}

void TopView::slot_setNormalSwitch(QString switchName)
{
    if(switchName=="H1"||switchName=="H2"){
        qDebug()<<__FILE__<<__LINE__<<"\n"
               <<"正常显示H1 H2: normalswitchpix_core"
               <<"\n";
        m_switch_map[switchName]->pix->setPixmap(normalswitchpix_core);
    }
    else{
        qDebug()<<__FILE__<<__LINE__<<"\n"
               <<"正常显示普通交换机 normalswitchpix"
               <<"\n";
        m_switch_map[switchName]->pix->setPixmap(normalswitchpix);
    }

}
TopView::~TopView()
{
    for (int i=0;i<m_all_line.size();i++)
     {
         QGraphicsLineItem *ql=m_all_line.at(i);
         if(ql)
             delete ql;
     }
     QMap<QString,Switcher*>::iterator it;
     for (it=m_switch_map.begin(); it!=m_switch_map.end();  ++it)
     {
         Switcher * line_swi = it.value();
         if(line_swi)
         {
            delete line_swi;
         }
     }
     QMap<QString,int*>::iterator itp;
     for (itp =portsState.begin(); itp!=portsState.end(); ++itp)
     {
         int * pp = itp.value();
         if(pp)
         {
            delete pp;
            pp=NULL;
         }
     }
    QFont font_t("Times",16);
    m_switch_map.clear();
    m_all_line.clear();
    m_all_line_pos.clear();
    portsState.clear();
    scene->clear();
    if(m_select_item)delete m_select_item;
    if(m_moving_item)delete m_moving_item;
}
void TopView::mouseReleaseEvent(QMouseEvent *event)
{
       if(is_press==true&&m_moving_item!=NULL)
       {
           save_to_file();
           is_press=false;
       }

       QGraphicsView::mouseReleaseEvent(event);
}

void TopView::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton )
     {

     QTransform transform;
     QPointF scene_pos= QGraphicsView::mapToScene(event->pos());
     move_last_pos=scene_pos;
     move_now_pos=scene_pos;
     QGraphicsItem *ff=scene->itemAt(scene_pos,transform);
     if(ff!=NULL)
     {
         if(ff->type()==MyGraphicsPixmapItem::Type)
         {
              is_press=true;
              m_moving_item=(MyGraphicsPixmapItem*)ff;

         }
     }

    }

    QGraphicsView::mousePressEvent(event);

}
void TopView::slot_moving(QPoint pos)
{

}
void TopView::mouseMoveEvent(QMouseEvent *event)//交换机图标不可移动
{
/*
     if(is_press==true&&m_moving_item!=NULL)     {

         QPointF scene_pos= QGraphicsView::mapToScene(event->pos());
           move_now_pos=scene_pos;

         if(scene_pos.x()<-(scene->width()/2)||scene_pos.x()>(scene->width()/2))
         {
              move_now_pos=  move_last_pos;


         }
         if(scene_pos.y()<-(scene->height()/2)||scene_pos.y()>(scene->height()/2))
         {
           move_now_pos=  move_last_pos;

         }

         QPointF diff=move_now_pos-move_last_pos;

         QString map_key=m_moving_item->getPixName();
         Switcher *swi=m_switch_map[map_key];

         QPointF picturecenter(normalswitchpix.width ()/2,normalswitchpix.height ()/2);
         swi->setPos(swi->getPos()+diff);
         swi->pix->setPos(swi->getPos()-picturecenter);
         swi->text->setPos(swi->getPos().x()-picturecenter.x(),swi->getPos().y()+5+normalswitchpix.height()-picturecenter.y());

         for(int j=0;j<swi->p_line_list.size();j++)
         {
             QGraphicsLineItem *temp=swi->p_line_list.at(j);
             int index_t=m_all_line.indexOf(temp);
             QString obj_name=m_all_line_pos.at(index_t).at(0)==map_key?m_all_line_pos.at(index_t).at(1):m_all_line_pos.at(index_t).at(0);
             Switcher *obj_swi=m_switch_map[obj_name];
             QLineF ll(swi->getPos(),obj_swi->getPos());
             temp->setLine(ll);
         }
         move_last_pos=move_now_pos;
     }

   QGraphicsView::mouseMoveEvent(event);
*/
}
void TopView::contextMenuEvent(QContextMenuEvent *event)//右键菜单去掉
{
/*
  QPointF scene_pos= QGraphicsView::mapToScene(event->pos());
  cur_pos=scene_pos;
  QGraphicsItem *ff=scene->itemAt(scene_pos);
  if(ff!=NULL)
  {

      if(ff->type()==MyGraphicsPixmapItem::Type)
      {
              m_select_item=((MyGraphicsPixmapItem*)ff);
              QCursor cur=this->cursor();
              QMenu *menu=new QMenu(this);
              QAction*del= menu->addAction(tr("删除交换机"));
              QAction*con= menu->addAction(tr("连接"));
              menu->addAction(tr("取消"));
              connect(del,SIGNAL(triggered()),this,SLOT(slot_delete()));
              connect(con,SIGNAL(triggered()),this,SLOT(slot_connect()));
              QPoint menu_pos(cur.pos().x()+5,cur.pos().y()+5);
              menu->exec(menu_pos);
              return;
       }


  }
    QCursor cur=this->cursor();
    QMenu *menu=new QMenu(this);
    QAction*add= menu->addAction(tr("添加交换机"));
    QAction* cancel=menu->addAction(tr("取消"));


    connect(add,SIGNAL(triggered()),this,SLOT(slot_add_switcher()));
    QPoint menu_pos(cur.pos().x()+5,cur.pos().y()+5);
    menu->exec(menu_pos);
   QGraphicsView::contextMenuEvent(event);
*/
}


bool TopView::checkRelatePort(QString nameA, QString nameB)
{
      QStringList strListA=nameA.split("-");
      QStringList strListB=nameB.split("-");

      //在m_switch_port_map中判断是否存在一组连接关系,其交换机名称也是A-B
      int portA = strListA[1].toInt();
      int portB = strListB[1].toInt();
      bool flag=false;
      QString nameRelA, nameRelB;
      nameRelA = strListA[0] +"-"+QString::number(portA+1);
      nameRelB = strListB[0] +"-"+QString::number(portB+1);

      if(m_switch_port_map.contains(nameRelA))
      {

          QString obj_sp=m_switch_port_map[nameRelA];
          if(obj_sp == nameRelB)
          {
                 if(portsState.contains(strListA[0]) && portsState.contains(strListB[0]))
                 {
                     flag=true;
                     int stateRelA, stateRelB;
                     stateRelA = portsState[strListA[0]][portA+1];
                     stateRelB = portsState[strListB[0]][portB+1];
                     if((stateRelA == switchUp || stateRelA == switchWarn)&&(stateRelB == switchUp || stateRelB == switchWarn ))
                     {
                         return true;
                     }
                     else
                     {
                         return false;
                     }
                 }
          }
      }

      nameRelA = strListA[0] +"-"+QString::number(portA-1);
      nameRelB = strListB[0] +"-"+QString::number(portB-1);
      if(m_switch_port_map.contains(nameRelA))
      {
          QString obj_sp=m_switch_port_map[nameRelA];
          if(obj_sp == nameRelB)
          {
                 if(portsState.contains(strListA[0]) && portsState.contains(strListB[0]))
                 {
                     flag=true;
                     int stateRelA, stateRelB;
                     stateRelA = portsState[strListA[0]][portA-1];
                     stateRelB = portsState[strListB[0]][portB-1];
                     if((stateRelA == switchUp || stateRelA == switchWarn)&&(stateRelB == switchUp || stateRelB == switchWarn ))
                     {
                         return true;
                     }
                     else
                     {
                         return false;
                     }
                 }
          }
      }
      if(flag==false)//不存在第二条链路，直接返回false
          return false;
}


void TopView::slot_portStatus(QString name,int index ,int state)//根据发过来的交换机端口状态信号更新拓扑图连线
{

    if(!portsState.contains(name))
    {
        portsState[name]=new int [60];
        for(int j=0;j<60;j++)
            portsState[name][j]=0;
    }
   //if( portsState[name][index]!=state)
    {
    portsState[name][index]=state;
    QString sp_name=name+"-"+QString::number(index);

    if(m_switch_port_map.contains(sp_name))//根据端口状态判断交换机是否存在真实连接
    {
                    QString obj_sp=m_switch_port_map[sp_name];
                    QStringList strList=obj_sp.split("-");
                    Switcher * swi=m_switch_map[name];
                    Switcher * obj_swi=m_switch_map[strList[0]];

                    if(portsState.contains(strList[0]))
                     {

                         int objState=portsState[strList[0]][strList[1].toInt()];//得到目标交换机的端口状态
                         mutex.lock();
                         if(swi->obj_swi_name_list.contains(strList[0]))//如果交换机的已连接对象中包含目标交换机，则直接判断
                         {

                             QString s_name=strList[0];
                             int index_t=swi->obj_swi_name_list.indexOf(s_name);
                             QGraphicsLineItem *temp=swi->p_line_list.at(index_t);

                             if(((state == switchUp || state == switchWarn)&&(objState == switchUp || objState == switchWarn ))||checkRelatePort(sp_name,obj_sp))//存在实际连接
                             {
                                 QPen linepen(QBrush(QColor(39,72,98)),2,Qt::SolidLine);
                                 QLineF ll(swi->getPos(),obj_swi->getPos());
                                 temp->setPen(linepen);
                                 temp->setLine(ll);
                             }
                             else//实际连接断开
                             {
                                 QPen linepen(QBrush(QColor(255,245,247)),2,Qt::DashDotLine);
                                 QLineF ll(swi->getPos(),obj_swi->getPos());
                                  temp->setPen(linepen);
                                  temp->setLine(ll);
                                  //这里要发出信号插入数据库
                                  emit signal_disconnected(sp_name+"~"+m_switch_port_map[sp_name]);
                             }
                         }
                         else//如果交换机的已连接对象中不包含目标交换机，则增加一条连线
                         {
                             if(((state == switchUp || state == switchWarn)&&(objState == switchUp || objState == switchWarn ))||checkRelatePort(sp_name,obj_sp))//存在实际连接
                             {
                                 QString s_name=strList[0];
                                 QPen linepen(QBrush(QColor(39,72,98)),2,Qt::SolidLine);
                                 QLineF ll(swi->getPos(),obj_swi->getPos());
                                 QGraphicsLineItem *line=scene->addLine(ll,linepen);
                                 line->setZValue (-1);

                                 swi->p_line_list.append(line);
                                 swi->obj_swi_name_list<<s_name;
                                 obj_swi->p_line_list.append(line);
                                 obj_swi->obj_swi_name_list<<name;

                                 m_all_line.append(line);
                                 QList<QString> line_pos_t;
                                 line_pos_t<<s_name<<name;
                                 m_all_line_pos<<line_pos_t;
                             }
                             else//实际链接不存在
                            {
                                 QString s_name=strList[0];
                                 QPen linepen(QBrush(QColor(255,245,247)),2,Qt::DashDotLine);
                                 QLineF ll(swi->getPos(),obj_swi->getPos());
                                 QGraphicsLineItem *line=scene->addLine(ll,linepen);
                                 line->setZValue (-1);

                                 swi->p_line_list.append(line);
                                 swi->obj_swi_name_list<<s_name;
                                 obj_swi->p_line_list.append(line);
                                 obj_swi->obj_swi_name_list<<name;

                                 m_all_line.append(line);
                                 QList<QString> line_pos_t;
                                 line_pos_t<<s_name<<name;
                                 m_all_line_pos<<line_pos_t;
                             }

                         }

                       //   save_to_file();
                        mutex.unlock();
            }
         }
    }
}
void TopView::slot_delete()
{
    QString map_key=m_select_item->getPixName();
    Switcher * swi=m_switch_map[map_key];
    if(swi->pix)
    {
        scene->removeItem(swi->pix);

    }
    if(swi->text)
    {
        scene->removeItem(swi->text);

    }

    for ( int i=0; i<swi->p_line_list.size(); ++i )
    {
        QGraphicsLineItem * temp=swi->p_line_list.at(i);
       if (temp)
       {
           QMap<QString,Switcher*>::iterator it;
           for ( it = m_switch_map.begin(); it != m_switch_map.end(); ++it ) {
               Switcher * line_swi=it.value();
               if(line_swi->p_line_list.contains(temp) && map_key!=it.key())
               {
                   int index_l=line_swi->p_line_list.indexOf(temp);
                   line_swi->obj_swi_name_list.removeAt(index_l);
                   line_swi->p_line_list.removeOne(temp);
               }
           }

//           m_all_line.removeOne(temp);
//           scene->removeItem(temp);
       }
    }

     QList<QGraphicsLineItem *> ::iterator it;
     for(it=swi->p_line_list.begin();it!=swi->p_line_list.end();it++)
     {
         QGraphicsLineItem * temp=(QGraphicsLineItem*)(*it);
         if(temp)
         {
           int index_l=swi->p_line_list.indexOf(temp);
           swi->obj_swi_name_list.removeAt(index_l);
           swi->p_line_list.removeOne(temp);

           index_l=m_all_line.indexOf(temp);
           m_all_line.removeAt(index_l);
           m_all_line_pos.removeAt(index_l);

           scene->removeItem(temp);
         }
     }
     m_switch_map.remove(map_key);
     save_to_file();

     QSqlQuery query("",DBConnection::db);;
     query.prepare("delete from switch where name=?");
     query.bindValue(0,map_key);
     query.exec();
     query.finish();
     query.clear();
     emit signal_update();
}
void TopView::slot_connect()
{
   QStringList select_list;
   QStringList unselect_list;
   QString map_key=m_select_item->getPixName();
   Switcher * swi=m_switch_map[map_key];
   QMap<QString,Switcher*>::iterator it;
   for ( it = m_switch_map.begin(); it != m_switch_map.end(); ++it ) {
       if(it.key()!=map_key)
       {
          if(swi->obj_swi_name_list.contains(it.key()))
          {
              select_list<<it.key();
          }
          else
          {
              unselect_list<<it.key();
          }
       }
   }

   AddLine addLineDialog(unselect_list,select_list);
   addLineDialog.setWindowTitle("连接");
   if(addLineDialog.exec())
   {

     for(int i=0;i<addLineDialog.select_list->count();i++)
     {
         if(!swi->obj_swi_name_list.contains(addLineDialog.select_list->item(i)->text()))
         {
             QString s_name=addLineDialog.select_list->item(i)->text();
             Switcher *obj_swi=m_switch_map[s_name];


             QPen linepen(QBrush(QColor(114,111,128)),2,Qt::DashLine);
             QLineF ll(swi->getPos(),obj_swi->getPos());
             QGraphicsLineItem *line=scene->addLine(ll,linepen);
             line->setZValue (-1);

             swi->p_line_list.append(line);
             swi->obj_swi_name_list<<s_name;
             obj_swi->p_line_list.append(line);
             obj_swi->obj_swi_name_list<<map_key;

             m_all_line.append(line);
             QList<QString> line_pos_t;
             line_pos_t<<s_name<<map_key;
             m_all_line_pos<<line_pos_t;
         }
     }
     for(int i=0;i<addLineDialog.unselect_list->count();i++)
     {
         if(swi->obj_swi_name_list.contains(addLineDialog.unselect_list->item(i)->text()))
         {
             QString s_name=addLineDialog.unselect_list->item(i)->text();
             int index_t=swi->obj_swi_name_list.indexOf(s_name);
             QGraphicsLineItem *line=swi->p_line_list.at(index_t);

             Switcher *obj_swi=m_switch_map[s_name];

             obj_swi->p_line_list.removeOne(line);
             obj_swi->obj_swi_name_list.removeOne(map_key);
             swi->p_line_list.removeOne(line);
             swi->obj_swi_name_list.removeOne(s_name);

             m_all_line.removeOne(line);
             index_t=m_all_line.indexOf(line);
             m_all_line.removeAt(index_t);
             m_all_line_pos.removeAt(index_t);
             scene->removeItem(line);
             delete line;
         }
     }
   }
  save_to_file();
}

void TopView::slot_add_switcher()
{
    QFont font_t("Times",16);
    AddSwitchDialog aDialog;
    aDialog.setWindowTitle ("添加交换机");
    aDialog.setDialogFlag(true);
    aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);
    if (aDialog.exec()) {
        QString name = aDialog.switchNameLineEdit->text().trimmed();
        QString ip = aDialog.ipAddressLineEdit->text().trimmed();
        QString location = aDialog.locationEdit->text().trimmed();
        QString remark = aDialog.remarkEdit->currentText().trimmed();
        QString community= "public";

        if(name==""||ip==""||location=="")
        {
            QMessageBox::information(0,"信息错误","请填写详细内容信息!");
            return;
        }

        QMap<QString,Switcher*>::iterator it;
        for ( it = m_switch_map.begin(); it != m_switch_map.end(); ++it ) {
            if(name==it.value()->getName())
            {
                QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(0, tr("提醒"), "已存在该交换机名称，请重新输入");
                    if (reply == QMessageBox::Ok)
                       slot_add_switcher();
                return;
            }
        }
        Switcher *swi=new Switcher();
        swi->setName(name);
        swi->setIp(ip);
        swi->setComunity(community);



        QPointF picturecenter(normalswitchpix.width ()/2,normalswitchpix.height ()/2);
        MyGraphicsPixmapItem *pix=new MyGraphicsPixmapItem();
        QString pix_name=swi->getName();
        pix->setPixName(pix_name);
        pix->setPixmap(normalswitchpix);
        pix->setFlag(QGraphicsItem::ItemIsSelectable);
        pix->setPos(cur_pos-picturecenter);
        scene->addItem(pix);
        swi->pix=pix;
        swi->setPos(cur_pos.x(),cur_pos.y());

        swi->text = new QGraphicsTextItem(name);
        swi->text->setFont(font_t);
        swi->text->setDefaultTextColor(QColor(3,101,100));
        swi->text->setPos(cur_pos.x()-picturecenter.x(),cur_pos.y()+5+normalswitchpix.height()-picturecenter.y());
        scene->addItem(swi->text);

        m_switch_map.insert(swi->getName(),swi);
        save_to_file();

        QSqlQuery sqlquery("",DBConnection::db);
        sqlquery.prepare("insert into switch (location,name,IP,community,remark)  values(?,?,?,?,?)");
        sqlquery.bindValue(0,location);
        sqlquery.bindValue(1,name);
        sqlquery.bindValue(2,ip);
        sqlquery.bindValue(3,community);
        sqlquery.bindValue(4,remark);
        sqlquery.exec();
        sqlquery.finish();
        sqlquery.clear();
        emit signal_update();

    }

}

void TopView::slot_ChangePixItem(int switchnumber,int alarmlevel) //alarmlevel:0-normal,1-warning,2-down
{
    qDebug()<<alarmlevel;
    if(alarmlevel==0)
    ;//pixitem[switchnumber-1]->setPixmap(QPixmap(":/img/switch/normalswitch"));
    else if (alarmlevel==1)
   ;// pixitem[switchnumber-1]->setPixmap(QPixmap(":/img/switch/warningswitch"));
    ;//else pixitem[switchnumber-1]->setPixmap(QPixmap(":/img/switch/downswitch"));

}


void TopView::addline(int startpix,int stoppix)
{
    QPen linepen(QBrush(QColor(114,111,128)),2,Qt::DashLine);
    QPointF picturecenter(normalswitchpix.width ()/2,normalswitchpix.height ()/2);
 //   scene->addLine (pixitem[startpix]->mapToScene (picturecenter).x (),pixitem[startpix]->mapToScene (picturecenter).y (),pixitem[stoppix]->mapToScene (picturecenter).x (),pixitem[stoppix]->mapToScene (picturecenter).y(),linepen)->setZValue (-1);

}

void TopView::slot_SeletedSwitchNumber()
{
    if (!scene->selectedItems ().isEmpty ())
    {
        MyGraphicsPixmapItem* item=(MyGraphicsPixmapItem*)scene->selectedItems ().at(0);

        emit signal_switchSelected(item->getPixName(),m_switch_map[item->getPixName()]->getType());

    }

}



void  TopView::save_to_file()
{
    QSqlQuery  query("",DBConnection::db);
    query.prepare("delete from switch_topo");
    query.exec();

    query.prepare("delete from switch_line");
    query.exec();

    QMap<QString,Switcher*>::iterator it;
    for(it=m_switch_map.begin();it!=m_switch_map.end();it++)
    {
        QString insert_sql = "insert into switch_topo values (?, ?, ?,?,?)";
        query.prepare(insert_sql);
        query.addBindValue(it.value()->getName());
        query.addBindValue(it.value()->getIP());
        query.addBindValue(it.value()->getComunity());
        QPointF pos_t=it.value()->getPos();
        query.addBindValue(pos_t.x());
        query.addBindValue(pos_t.y());
        query.exec();
    }

    for(int i=0;i<m_all_line.size();i++)
    {
        QString insert_sql = "insert into switch_line(pos_x1,pos_y1,pos_x2,pos_y2,switch_name1,switch_name2) values (?,?,?,?,?,?)";
        query.prepare(insert_sql);
        query.bindValue(0,m_all_line.at(i)->line().x1());
        query.bindValue(1,m_all_line.at(i)->line().y1());
        query.bindValue(2,m_all_line.at(i)->line().x2());
        query.bindValue(3,m_all_line.at(i)->line().y2());
        query.bindValue(4,m_all_line_pos.at(i).at(0));
        query.bindValue(5,m_all_line_pos.at(i).at(1));
        query.exec();

    }
query.finish();
query.clear();
}

