#ifndef __BAB_REGISTRY_H__
#define __BAB_REGISTRY_H__

#include <glib-object.h>
/*
 * Potentially, include other headers on which this header depends.
 */

/*
 * Type macros.
 */
#define BAB_TYPE_REGISTRY                  (bab_registry_get_type ())
#define BAB_REGISTRY(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), BAB_TYPE_REGISTRY, BabRegistry))
#define BAB_IS_REGISTRY(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BAB_TYPE_REGISTRY))
#define BAB_REGISTRY_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), BAB_TYPE_REGISTRY, BabRegistryClass))
#define BAB_IS_REGISTRY_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), BAB_TYPE_REGISTRY))
#define BAB_REGISTRY_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), BAB_TYPE_REGISTRY, BabRegistryClass))

typedef struct _BabRegistry        BabRegistry;
typedef struct _BabRegistryClass   BabRegistryClass;

struct _BabRegistry
{
    /* Parent instance structure */
    GObject parent_instance;

    /* instance members */
};

struct _BabRegistryClass
{
    /* Parent class structure */
    GObjectClass parent_class;

    /* class members */
};

/* used by BAB_TYPE_REGISTRY */
GType bab_registry_get_type(void);

/*
 * Method definitions.
 */

#endif /* __BAB_REGISTRY_H__ */
