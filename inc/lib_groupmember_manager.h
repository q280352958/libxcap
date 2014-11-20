#ifndef _LIB_GROUPMEMBER_MANAGER_H_
#define _LIB_GROUPMEMBER_MANAGER_H_

typedef struct _groupmember_request groupmember_request;
typedef struct _groupmember_list groupmember_list;

/**
 * Create an empty GROUPMEMBER REQUEST object
 *
 * \return a new GROUPMEMBER REQUEST object
 */
groupmember_request *
groupmember_request_new();

/**
 * Destory GROUPMEMBER REQUEST object
 *
 * \param a_request GROUPMEMBER REQUEST object
 */
void
groupmember_request_destroy(groupmember_request *a_request);

/**
 * Create an empty GROUPMEMBER LIST object
 *
 * \return a new GROUPMEMBER LIST object
 */
groupmember_list *
groupmember_list_new();

/**
 * Destory GROUPMEMBER LIST object
 *
 * \param a_list GROUPMEMBER LIST object
 */
void
groupmember_list_destroy(groupmember_list *a_list);

/**
 * Parse GROUPMEMBER LIST content
 *
 * \param a_request GROUP REQUEST object
 * \param a_list GROUP LIST object
 * \return 0 success , -1 fail
 */
int
groupmember_list_parse(groupmember_request *a_request, groupmember_list *a_list);

/**
 * Add a group member
 *
 * \param a_request GROUPMEMBER REQUEST object
 * \return 0 success , -1 fail
 */
int
groupmember_member_add(groupmember_request *a_request);

/**
 * Delete a group member
 *
 * \param a_request GROUPMEMBER REQUEST object
 * \return 0 success , -1 fail
 */
int
groupmember_member_del(groupmember_request *a_request);

/**
 * Query group member lists
 *
 * \param a_request GROUPMEMBER REQUEST object
 * \param a_list GROUPMEMBER LIST object
 * \return 0 success , -1 fail
 */
int
groupmember_member_query(groupmember_request *a_request, groupmember_list *a_list);

/**
 * Administrator update group member list
 *
 * \param a_request GROUPMEMBER REQUEST object
 * \return 0 success , -1 fail
 */
int
groupmember_admin_update(groupmember_request *a_request);

/**
 * User update group member list
 *
 * \param a_request GROUPMEMBER REQUEST object
 * \return 0 success , -1 fail
 */
int
groupmember_user_update(groupmember_request *a_request);

#endif