#ifndef _GROUP_MANAGER_H_
#define _GROUP_MANAGER_H_

typedef struct _group_request group_request;
typedef struct _group_list group_list;

/**
 * Create an empty GROUP REQUEST object
 *
 * \return a new GROUP REQUEST object
 */
group_request *
group_request_new();

/**
 * Destory GROUP REQUEST object
 *
 * \param a_request GROUP REQUEST object
 */
void
group_request_destory(group_request *a_request);

/**
 * Create an empty GROUP LIST object
 *
 * \return a new GROUP LIST object
 */
group_list *
group_list_new();

/**
 * Destory GROUP LIST object
 *
 * \param a_list GROUP LIST object
 */
void
group_list_destory(group_list *a_list);

/**
 * Parse GROUP LIST content
 *
 * \param a_request GROUP REQUEST object
 * \param a_list GROUP LIST object
 * \return 0 success , -1 fail
 */
int
group_list_parse(group_request *a_request, group_list *a_list);

/**
 * Craete a group
 *
 * \param a_request GROUP REQUEST object
 * \return 0 success , -1 fail
 */
int
group_create(group_request *a_request);

/**
 * Delete a group
 *
 * \param a_request GROUP REQUEST object
 * \return 0 success , -1 fail
 */
int
group_del(group_request *a_request);

/**
 * Query group lists
 *
 * \param a_request GROUP REQUEST object
 * \param a_list GROUP LIST object
 * \return 0 success , -1 fail
 */
int
group_query(group_request *a_request, group_list *a_list);

#endif