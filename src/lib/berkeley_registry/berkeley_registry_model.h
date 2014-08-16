// branch 0
// \_ branch Documents
//    \_ leaf something.doc
//       \_ version 1
// \_ branch Downloads

typedef struct branch_struct Branch;
typedef struct leaf_struct Leaf;
typedef struct version_struct Version;

struct branch_struct
{
    gchar *name;
    int parent;
    int *branches;
    int *leaves;
};

struct leaf_struct
{
    gchar *name;
    Branch *parent;
    Version *versions;
};

struct version_struct
{
    Leaf *parent;
    int size;
    int mtime;
    Checksum *checksum;
};
