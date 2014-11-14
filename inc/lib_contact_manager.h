#ifndef _CONTACT_MANAGER_H_
#define _CONTACT_MANAGER_H_

typedef struct _contact_request contact_request;
typedef struct _contact_list contact_list;

/**
 * Create an empty CONCTACT REQUEST object
 *
 * \return a new CONCTACT REQUEST object
 */
contact_request *
contact_request_new();

/**
 * Destory CONCTACT REQUEST object
 *
 * \param a_request CONCTACT REQUEST object
 */
void
contact_request_destory(contact_request *a_request);

/**
 * Create an empty CONCTACT LIST object
 *
 * \return a new CONCTACT LIST object
 */
contact_list *
contact_list_new();

/**
 * Destory CONCTACT LIST object
 *
 * \param a_list CONCTACT LIST object
 */
void
contact_list_destory(contact_list *a_list);

/**
 * Parse CONCTACT LIST content
 *
 * \param a_request CONCTACT REQUEST object
 * \param a_list CONCTACT LIST object
 * \return 0 success , -1 fail
 */
int
contact_list_parse(contact_request *a_request, contact_list *a_list);

/**
 * Add a contact
 *
 * \param a_request CONCTACT REQUEST object
 * \return 0 success , -1 fail
 */
int
contact_add(contact_request *a_request);

/**
 * Delete a contact
 *
 * \param a_request CONCTACT REQUEST object
 * \return 0 success , -1 fail
 */
int
contact_del(contact_request *a_request);

/**
 * Query contact lists
 *
 * \param a_request CONCTACT REQUEST object
 * \param a_list CONTACT LIST object
 * \return 0 success , -1 fail
 */
int
contact_query(contact_request *a_request, contact_list *a_list);


#endif