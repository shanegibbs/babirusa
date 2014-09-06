#ifndef BERKELEY_REGISTRY_H
#define BERKELEY_REGISTRY_H

// branch 0
// \_ branch Documents
//    \_ leaf something.doc
//       \_ version 1
// \_ branch Downloads

typedef struct Branch Branch;
typedef struct Leaf Leaf;
typedef struct Version Version;

struct Branch
{
    gchar *name;
    Branch *parent;
    Branch *branches;
    Leaf *leaves;
};

struct Leaf
{
    gchar *name;
    Branch *parent;
    Version *versions;
};

struct Version
{
    Leaf *parent;
    int size;
    int mtime;
    Checksum *checksum;
};

#endif
