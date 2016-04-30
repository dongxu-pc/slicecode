class abstract_db:DB的抽象借口，可以借其实现不同系统的benchmark使用统一的接口；

txn.h
class transaction_base:事务的基类，只含有简单的定义；
	enum txn_state:
		TXN_EMBRYO:事务对象已经被建立但还没有进行任何操作,作为一个事务建立时的初始状态
		TXN_ACTIVE:
		TXN_COMMIT:
		TXN_ABRT:
	tid

class transaction:public transaction_base:事务类
	read_set,write_set,absent_set;
	sa,rcu_guard_;
	gen_commit_tid(write_tuples);
	can_read_tid(tid_t);
	on_dbtuple_spill();
	on_logical_delete();
	on_tid_finish(commit_tid);
	on_post_rcu_region_completion();

class transaction_abort_exception : public std::execption:事务异常退出
	transaction_base::abort_reason r;
	get_reason();
	what();

struct txn_epoch_sync:
	sync():阻塞直到下一个epoch
	finish():完成所有的异步jobs
	thread_end():
	compute_ntxn_persisted()

	
tuple.h
struct dbtuple:用于存储潜在的（非事务）数据结构
	version_t,node_size_type,tid_t;
	record_type,const_record_type,size_type,string_type
	MIMN_TID=0,MAX_TID=tid_t-1;

base_txn_btree.h
class base_txn_btree:


