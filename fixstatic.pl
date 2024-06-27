#!/usr/bin/perl -pi

if (/,/ || /=/) {
    s/static/nosave/;
}
elsif (/\([^{[:]/) {
    s/static/protected/;
}
elsif (/;/) {
    s/static/nosave/;
}
else {
    s/static/protected/;
}