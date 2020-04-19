include ./config.mk

default:
	make -C $(COMMON)/logManage
	make -C $(SERVER)/serveMain
	make -C $(CLIENT)/clientMain

clean:
	make -C $(COMMON)/logManage    clean
	make -C $(SERVER)/serveMain    clean
	make -C $(CLIENT)/clientMain   clean