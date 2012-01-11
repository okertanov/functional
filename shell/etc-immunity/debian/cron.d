#
# Regular cron jobs for the etc-immunity package
#
0 4	* * *	root	[ -x /usr/bin/etc-immunity_maintenance ] && /usr/bin/etc-immunity_maintenance
