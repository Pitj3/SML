#include <stdio.h>
#include <sml.h>

int main()
{
    printf("Major: %d, Minor: %d, Revision: %d\n", sml::version.major, sml::version.minor, sml::version.revision);
    printf("%f\n", constants::pi);

    vec2<float> v;

    return 0;
}