void LinkedList_Select_Sort(LinkedList &L){
	//单链表上的简单选择排序算法
	for(p=L;p->next->next;p=p->next){
		q=p->next;
		x=q->data;
		for(r=q,s=q;r->next;r=r->next) 
			if(r->next->data<x){
				x=r->next->data;
				s=r;
			}
			if(s!=q){
				p->next=s->next;
				s->next=q;
				t=q->next;
				q->next=p->next->next;
				p->next->next=t;
			} 
	}
}