#include <stdio.h>
#include <sml.h>

int main()
{
    printf("Major: %d, Minor: %d, Revision: %d\n", sml::version.major, sml::version.minor, sml::version.revision);
    printf("%f\n", constants::pi);

    sml::fvec2 v = sml::fvec2(10.0f, 10.0f);

    printf("%s\n", v.toString().c_str());

    return 0;
}