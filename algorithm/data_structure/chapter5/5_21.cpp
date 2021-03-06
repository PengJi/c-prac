void TSMatrixAdd(TSMatrix A,TSMatrix B,TSMatrix &C){
	//三元组顺序表表示的稀疏矩阵加法
	C.mu=A.mu;
	C.nu=A.nu;
	C.tu=0;
	pa=1;
	pb=1;
	pc=1;
	for(x=1;x<=A.mu;x++){
		while(A.data[pa].i<x)
			pa++;
		while(B.data[pb].i<x)
			pb++;
		while(A.data[pa].i==x && B.data[pb].i==x){//行列值都相等的元素
			if(A.data[pa].j==B.data[pb].j){
				ce=A.data[pa].e+B.data[pb].e;
				if(ce){
					C.data[pc].i=x;
					C.data[pc].j=A.data[pa].j;
					C.data[pc].e=ce;
					pa++;
					pb++;
					pc++;
				}
			}else if(A.data[pa].j>B.data[pb].j){
				C.data[pc].i=x;
				C.data[pc].j=B.data[pb].j;
				C.data[pc].e=B.datA[pb].e;
				pb++;
				pc++;
			}else{
				C.data[pc].i=x;
				C.data[pc].j=A.data[pa].j;
				C.data[pc].e=A.data[pa].e;
				pa++;
				pc++;
			}
		}
		while(A.data[pa]==x){//c插入A中剩余的元素
			C.data[pc].i=x;
			C.data[pc].j=A.data[pa].j;
			C.data[pc].e=A.data[pa].e;
			pa++;
			pc++;
		}
		while(B.data[pb]==x){//插入B中剩余的元素
			C.data[pc].i=x;
			C.data[pc].j=B.data[pb].j;
			C.data[pc].e=B.data[pb].e;
			pb++;
			pc++;
		}
	}
	C.tu=pc;
}