import re
tnsblock = 'CMS_ORCON_LB=(
	DESCRIPTION=
	(ADDRESS= (PROTOCOL=TCP) (HOST=cmsonr3-s.cern.ch) (PORT=10121) )
	(ADDRESS= (PROTOCOL=TCP) (HOST=cmsonr4-s.cern.ch) (PORT=10121) )
	(ADDRESS= (PROTOCOL=TCP) (HOST=cmsonr2-s.cern.ch) (PORT=10121) )
	(ADDRESS= (PROTOCOL=TCP) (HOST=cmsonr1-s.cern.ch) (PORT=10121) )
	(LOAD_BALANCE=on)
	(ENABLE=BROKEN)
	(CONNECT_DATA=
		(SERVER=DEDICATED)
		(SERVICE_NAME=cms_orcon_lb.cern.ch)
	)
)'

 pattern = "cms"
