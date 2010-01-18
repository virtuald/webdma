#! /bin/sh


dirs="$*"
if test _"$dirs" = _
then dirs="."
fi

for dir in $dirs
do
    if test -d $dir
    then
	aclocal=""
	autoconf=" && autoconf"
	autoheader=""
	automake=""

	if test -f $dir/Makefile.am
	then
		aclocal=" && aclocal -I ."
		automake=" && automake --copy --add-missing"

		if egrep 'A[CM]_PROG_LIBTOOL' $dir/configure.ac >/dev/null
		then
			libtoolize=" && libtoolize --copy --automake"
		fi
	fi

	if egrep 'A[CM]_CONFIG_HEADER' $dir/configure.ac >/dev/null
	then autoheader=" && autoheader"
	fi

	commands="cd $dir${libtoolize}${aclocal}${autoheader}${autoconf}${automake}"
	echo "$commands"

	eval "($commands)"
	result=$?
	if test $result -ne 0
	then exit $result
	fi
    fi
done

exit $result
