#include <stdio.h>
#include <cstring>
#include "mysql.h"

#pragma warning(disable:4996)
#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "xnejfdl100!";
const char* db = "20191098_project";

using namespace std;

int main(void) {
	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	FILE* fp = fopen("20191098.txt", "rt");
	if (mysql_init(&conn) == NULL) {
		printf("mysql_init() error");
		return 1;
	}

	connection = mysql_real_connect(&conn, host, user, pw, NULL, 3306, (const char*)NULL, 0);
	if (connection == NULL) {
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}
	else {
		printf("Connection clear\n");

		char buffer[20000];
		
		if (fp == NULL) {
			printf("file does not exist!\n");
			return 1;
		}

	
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
			if (!strcmp(buffer, "$$$\n"))      // read lines from CRUD file, '$$$' separates CREATE / DELETE parts.
				break;
			mysql_query(connection, buffer);
		}

		

		if (mysql_select_db(&conn, db)) {
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		bool main_flag = false;
		int state = 0;
		while (!main_flag) {
			int type_num;

			printf("-------- SELECT QUERY TYPES --------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			printf("Type number of which number Type ");
			scanf("%d", &type_num);

			if (type_num == 1) {
				printf("\n------- TYPE 1 -------\n");
				printf("** Find address of homes for sale in the district 'Mapo'.**\n");
				char query[] = "SELECT Property.address FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.District = 'Mapo' AND Transaction.SalePrice IS NULL";
				printf("-------  Address ------- \n");
				state = mysql_query(connection, query);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				int subtype_num;
				bool subflag = false;
				while (!subflag) {
					printf("\n------- Subtypes in TYPE 1 -------\n");
					printf("\t1. TYPE 1-1.\n");
					printf("Type number of which number Type : ");
					scanf("%d", &subtype_num);

					if (subtype_num == 1) {
						printf("-------  TYPE 1-1 ------- \n");
						printf("** Then find the costing between ￦1,000,000,000 and ￦1,500,000,000.**\n");
						char subquery[] = "SELECT Property.address FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.District = 'Mapo' AND Transaction.SalePrice IS NULL AND Transaction.ListingPrice BETWEEN 1000000000 AND 1500000000";
						state = mysql_query(connection, subquery);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
					}
					else if (subtype_num == 0) {
						subflag = true;
						printf("\n");
					}
					else {
						printf("You typed wrong number\n");
						continue;
					}
				}
			}
			else if (type_num == 2) {
				printf("\n------- TYPE 2 -------\n");
				printf("** Find the address of homes for sale in the 8th school district.**\n");
				char query[] = "SELECT Property.address FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.District IN (SELECT District FROM District WHERE SchoolDistrict = 8) AND Transaction.SalePrice IS NULL";
				printf("\n-------  Address of 8th school ------- \n");
				state = mysql_query(connection, query);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				int subtype_num;
				bool subflag = false;
				while (!subflag) {
					printf("\n------- Subtypes in TYPE 2 -------\n");
					printf("\t1. TYPE 2-1.\n");
					printf("Type number of which number Type : ");
					scanf("%d", &subtype_num);

					if (subtype_num == 1) {
						printf("\n-------  TYPE 2-1 ------- \n");
						printf("** Then find properties with 4 or more bedrooms and 2 bathrooms.**\n");
						char subquery[] = "SELECT Property.address FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.District IN (SELECT District FROM District WHERE SchoolDistrict = 8) AND Transaction.SalePrice IS NULL AND Property.NumberOfBedrooms >= 4 AND Property.NumberOfBathrooms = 2";
						state = mysql_query(connection, subquery);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
					}
					else if (subtype_num == 0) {
						subflag = true;
						printf("\n");
					}
					else {
						printf("You typed wrong number\n");
						continue;
					}
				}
			}
			else if (type_num == 3) {
				/*
				// Display total sales per agent per year 3번 쿼리들이 맞는지 확인용
				printf("\n------- Total Sales per Agent per Year ------- \n");
				char total_sales_query[] = "SELECT YEAR(SaleDate) AS Year, Agent.Name, SUM(SalePrice) AS TotalSales FROM Transaction JOIN Agent ON Transaction.SellerAgentID = Agent.AgentID GROUP BY Year, Agent.Name ORDER BY Year, TotalSales DESC";
				state = mysql_query(connection, total_sales_query);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					printf("Year\tAgent Name\tTotal Sales\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s\t%s\t%s\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}
				*/

				printf("\n------- TYPE 3 -------\n");
				printf("** Find the name of the agent who has sold the most properties in the year 2022 by total won value.**\n");
				char query[] = "SELECT Agent.Name FROM Agent JOIN (SELECT SellerAgentID, SUM(SalePrice) AS TotalSale FROM Transaction WHERE YEAR(SaleDate) = 2022 GROUP BY SellerAgentID ORDER BY TotalSale DESC LIMIT 1) AS TopAgent ON Agent.AgentID = TopAgent.SellerAgentID";
				printf("\n-------  Agent Name ------- \n");
				state = mysql_query(connection, query);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}



				int subtype_num;
				bool subflag = false;
				while (!subflag) {
					printf("\n------- Subtypes in TYPE 3 -------\n");
					printf("\t1. TYPE 3-1.\n");
					printf("\t2. TYPE 3-2.\n");

					printf("Type number of which number Type ");
					scanf("%d", &subtype_num);

					if (subtype_num == 1) {

						int k;
						printf("Enter the value of k: ");
						scanf("%d", &k);
						printf("\n-------  TYPE 3-1 ------- \n");
						printf("** Then find the top k agents in the year 2023 by total won value.**\n");
						char subquery[300];
						sprintf(subquery, "SELECT Agent.Name FROM Agent JOIN (SELECT SellerAgentID, SUM(SalePrice) AS TotalSale FROM Transaction WHERE YEAR(SaleDate) = 2023 GROUP BY SellerAgentID ORDER BY TotalSale DESC LIMIT %d) AS TopAgents ON Agent.AgentID = TopAgents.SellerAgentID", k);
						state = mysql_query(connection, subquery);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
					}
					else if (subtype_num == 2) {
						printf("-------  TYPE 3-2 ------- \n");
						printf("** Find the bottom 10%% agents in the year 2021 by total won value.**\n");

						// First, calculate the number of agents to include in the bottom 10%
						char count_query[] = "SELECT COUNT(DISTINCT SellerAgentID) FROM Transaction WHERE YEAR(SaleDate) = 2021";
						state = mysql_query(connection, count_query);
						int agent_count = 0;
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								agent_count = atoi(sql_row[0]);
							}
							mysql_free_result(sql_result);
						}

						int bottom_10_percent_count = (int)(agent_count * 0.1);

						if (bottom_10_percent_count > 0) {
							char subquery[300];
							sprintf(subquery, "SELECT Agent.Name FROM Agent JOIN (SELECT SellerAgentID, SUM(SalePrice) AS TotalSale FROM Transaction WHERE YEAR(SaleDate) = 2021 GROUP BY SellerAgentID ORDER BY TotalSale ASC LIMIT %d) AS BottomAgents ON Agent.AgentID = BottomAgents.SellerAgentID ORDER BY TotalSale ASC", bottom_10_percent_count);
							state = mysql_query(connection, subquery);
							if (state == 0) {
								sql_result = mysql_store_result(connection);
								while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
									printf("%s\n", sql_row[0]);
								}
								mysql_free_result(sql_result);
							}
						}
						else {
							printf("No agents found for the bottom 10%% calculation.\n");
						}
					}
					else if (subtype_num == 0) {
						subflag = true;
						printf("\n");
					}
					else {
						printf("You typed wrong number\n");
						continue;
					}
				}
			}
			else if (type_num == 4) {
				printf("\n------- TYPE 4 -------\n");
				printf("** For each agent, compute the average selling price of properties sold in 2022, and the average time the property was on the market.**\n");
				char query[] = "SELECT Agent.Name, AVG(Transaction.SalePrice) AS AvgSellingPrice, AVG(DATEDIFF(Transaction.DateSold, Transaction.SaleDate)) AS AvgTimeOnMarket FROM Agent JOIN Transaction ON Agent.AgentID = Transaction.SellerAgentID WHERE YEAR(Transaction.SaleDate) = 2022 GROUP BY Agent.Name";
				printf("-------  Agent Average Selling Price and Time on Market in 2022 ------- \n");
				state = mysql_query(connection, query);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					printf("Agent Name\tAverage Selling Price\tAverage Time on Market (Days)\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("%s\t%s\t\t%s\n", sql_row[0], sql_row[1], sql_row[2]);
					}
					mysql_free_result(sql_result);
				}

				int subtype_num;
				bool subflag = false;
				while (!subflag) {
					printf("\n------- Subtypes in TYPE 4 -------\n");
					printf("\t1. TYPE 4-1.\n");
					printf("\t2. TYPE 4-2.\n");
					printf("Type number of which number Type ");
					scanf("%d", &subtype_num);

					if (subtype_num == 1) {
						printf("-------  TYPE 4-1 ------- \n");
						printf("** Then compute the maximum selling price of properties sold in 2023 for each agent.**\n");
						char subquery[] = "SELECT Agent.Name, MAX(Transaction.SalePrice) AS MaxSellingPrice FROM Agent JOIN Transaction ON Agent.AgentID = Transaction.SellerAgentID WHERE YEAR(Transaction.SaleDate) = 2023 GROUP BY Agent.Name";
						state = mysql_query(connection, subquery);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							printf("Agent Name\tMaximum Selling Price in 2023\n");
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\t%s\n", sql_row[0], sql_row[1]);
							}
							mysql_free_result(sql_result);
						}
					}
					else if (subtype_num == 2) {
						printf("-------  TYPE 4-2 ------- \n");
						printf("** And then compute the longest time the property was on the market for each agent.**\n");
						char subquery[] = "SELECT Agent.Name, MAX(DATEDIFF(Transaction.DateSold, Transaction.SaleDate)) AS LongestTimeOnMarket FROM Agent JOIN Transaction ON Agent.AgentID = Transaction.SellerAgentID GROUP BY Agent.Name";
						state = mysql_query(connection, subquery);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							printf("Agent Name\tLongest Time on Market (Days)\n");
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\t%s\n", sql_row[0], sql_row[1]);
							}
							mysql_free_result(sql_result);
						}
					}
					else if (subtype_num == 0) {
						subflag = true;
						printf("\n");
					}
					else {
						printf("Didn't I ask you to enter only one number???? \n");
						continue;
					}
				}
			}
			else if (type_num == 5) {
				printf("\n------- TYPE 5 -------\n");
				printf("** Show photos of the most expensive studio, one-bedroom, multi-bedroom apartment(s), and detached house(s), respectively, from the database. **\n");

				// Most expensive studio
				printf("\n------- Most Expensive Studio ------- \n");
				char query_studio[] = "SELECT Property.PropertyID FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.Type = 'Studio' ORDER BY Transaction.ListingPrice DESC LIMIT 1";
				state = mysql_query(connection, query_studio);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						char property_id[9];
						strcpy(property_id, sql_row[0]);
						mysql_free_result(sql_result);

						char photo_query[256];
						sprintf(photo_query, "SELECT Photo.image FROM Photo WHERE Photo.PropertyID = '%s'", property_id);
						state = mysql_query(connection, photo_query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
					}
				}

				// Most expensive one-bedroom apartment
				printf("\n------- Most Expensive One-Bedroom Apartment ------- \n");
				char query_one_bed[] = "SELECT Property.PropertyID FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.Type = 'Apartment' AND Property.NumberOfBedrooms = 1 ORDER BY Transaction.ListingPrice DESC LIMIT 1";
				state = mysql_query(connection, query_one_bed);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						char property_id[9];
						strcpy(property_id, sql_row[0]);
						mysql_free_result(sql_result);

						char photo_query[256];
						sprintf(photo_query, "SELECT Photo.image FROM Photo WHERE Photo.PropertyID = '%s'", property_id);
						state = mysql_query(connection, photo_query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
					}
				}

				// Most expensive multi-bedroom apartment
				printf("\n------- Most Expensive Multi-Bedroom Apartment ------- \n");
				char query_multi_bed[] = "SELECT Property.PropertyID FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.Type = 'Apartment' AND Property.NumberOfBedrooms > 1 ORDER BY Transaction.ListingPrice DESC LIMIT 1";
				state = mysql_query(connection, query_multi_bed);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						char property_id[9];
						strcpy(property_id, sql_row[0]);
						mysql_free_result(sql_result);

						char photo_query[256];
						sprintf(photo_query, "SELECT Photo.image FROM Photo WHERE Photo.PropertyID = '%s'", property_id);
						state = mysql_query(connection, photo_query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
					}
				}

				// Most expensive detached house
				printf("\n------- Most Expensive Detached House ------- \n");
				char query_house[] = "SELECT Property.PropertyID FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.Type = 'House' ORDER BY Transaction.ListingPrice DESC LIMIT 1";
				state = mysql_query(connection, query_house);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						char property_id[9];
						strcpy(property_id, sql_row[0]);
						mysql_free_result(sql_result);

						char photo_query[256];
						sprintf(photo_query, "SELECT Photo.image FROM Photo WHERE Photo.PropertyID = '%s'", property_id);
						state = mysql_query(connection, photo_query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%s\n", sql_row[0]);
							}
							mysql_free_result(sql_result);
						}
					}
				}
			}
			else if (type_num == 6) {
				printf("---- TYPE 6 ----\n\n");
				printf("** Record the sale of a property that had been listed as being available.**\n");

				// Query to fetch all unsold properties
				char fetch_unsold_query[] = "SELECT TransactionID FROM Transaction WHERE SalePrice IS NULL";
				state = mysql_query(connection, fetch_unsold_query);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					printf("------- Unsold Properties ------- \n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
						printf("Transaction ID: %s\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				else {
					printf("Failed to fetch unsold properties: %s\n", mysql_error(connection));
					return 1; // Exit if fetching unsold properties fails
				}

				char transaction_id[9], buyer_agent_id[9], date_sold[20], sale_price[20], buyer_id[9];
				bool valid_transaction_id = false, valid_buyer_agent_id = false, valid_buyer_id = false, valid_date_sold = false;

				// Validate Transaction ID
				while (!valid_transaction_id) {
					printf("Enter Transaction ID of the property to be marked as sold: ");
					scanf("%8s", transaction_id);

					// Check if entered Transaction ID is unsold
					char check_transaction_query[256];
					sprintf(check_transaction_query, "SELECT COUNT(*) FROM Transaction WHERE TransactionID = '%s' AND SalePrice IS NULL", transaction_id);
					state = mysql_query(connection, check_transaction_query);
					if (state == 0) {
						sql_result = mysql_store_result(connection);
						if ((sql_row = mysql_fetch_row(sql_result)) != NULL && atoi(sql_row[0]) > 0) {
							valid_transaction_id = true;
						}
						else {
							printf("Invalid Transaction ID. Please enter a valid unsold Transaction ID.\n");
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Failed to verify Transaction ID: %s\n", mysql_error(connection));
						return 1; // Exit if verifying Transaction ID fails
					}
				}

				// Validate Buyer Agent ID
				while (!valid_buyer_agent_id) {
					printf("Enter Buyer Agent ID: ");
					scanf("%8s", buyer_agent_id);

					// Check if entered Buyer Agent ID exists
					char check_agent_query[256];
					sprintf(check_agent_query, "SELECT COUNT(*) FROM Agent WHERE AgentID = '%s'", buyer_agent_id);
					state = mysql_query(connection, check_agent_query);
					if (state == 0) {
						sql_result = mysql_store_result(connection);
						if ((sql_row = mysql_fetch_row(sql_result)) != NULL && atoi(sql_row[0]) > 0) {
							valid_buyer_agent_id = true;
						}
						else {
							printf("Invalid Buyer Agent ID. Please enter a valid Buyer Agent ID.\n");
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Failed to verify Buyer Agent ID: %s\n", mysql_error(connection));
						return 1; // Exit if verifying Buyer Agent ID fails
					}
				}

				// Validate Buyer ID
				while (!valid_buyer_id) {
					printf("Enter Buyer ID: ");
					scanf("%8s", buyer_id);

					// Check if entered Buyer ID exists
					char check_buyer_query[256];
					sprintf(check_buyer_query, "SELECT COUNT(*) FROM Buyer WHERE BuyerID = '%s'", buyer_id);
					state = mysql_query(connection, check_buyer_query);
					if (state == 0) {
						sql_result = mysql_store_result(connection);
						if ((sql_row = mysql_fetch_row(sql_result)) != NULL && atoi(sql_row[0]) > 0) {
							valid_buyer_id = true;
						}
						else {
							printf("Invalid Buyer ID. Please enter a valid Buyer ID.\n");
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Failed to verify Buyer ID: %s\n", mysql_error(connection));
						return 1; // Exit if verifying Buyer ID fails
					}
				}

				// Validate Date Sold
				while (!valid_date_sold) {
					printf("Enter Date Sold (YYYY-MM-DD): ");
					scanf("%19s", date_sold);

					// Fetch SaleDate for the given TransactionID
					char fetch_sale_date_query[256];
					sprintf(fetch_sale_date_query, "SELECT SaleDate FROM Transaction WHERE TransactionID = '%s'", transaction_id);
					state = mysql_query(connection, fetch_sale_date_query);
					if (state == 0) {
						sql_result = mysql_store_result(connection);
						if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
							// Compare SaleDate and DateSold
							if (strcmp(sql_row[0], date_sold) <= 0) {
								valid_date_sold = true;
							}
							else {
								printf("Invalid Date Sold. It must be later than or equal to the SaleDate (%s).\n", sql_row[0]);
							}
						}
						mysql_free_result(sql_result);
					}
					else {
						printf("Failed to fetch SaleDate: %s\n", mysql_error(connection));
						return 1; // Exit if fetching SaleDate fails
					}
				}

				printf("Enter Sale Price: ");
				scanf("%19s", sale_price);

				char update_query[1024];
				sprintf(update_query, "UPDATE Transaction SET BuyerAgentID = '%s', BuyerID = '%s', DateSold = '%s', SalePrice = %s WHERE TransactionID = '%s' AND SalePrice IS NULL", buyer_agent_id, buyer_id, date_sold, sale_price, transaction_id);

				state = mysql_query(connection, update_query);
				if (state == 0) {
					printf("Transaction updated successfully.\n");

					// Commit the transaction
					if (mysql_commit(connection) == 0) {
						printf("Transaction committed successfully.\n");
					}
					else {
						printf("Failed to commit transaction: %s\n", mysql_error(connection));
					}
				}
				else {
					printf("Failed to update transaction: %s\n", mysql_error(connection));
				}
			}
			else if (type_num == 7) {
				printf("---- TYPE 7 ----\n\n");
				printf("** Add a new agent to the database.**\n");

				char agent_id[9], name[33], contact_info[33];
				printf("Enter Agent ID: ");
				scanf("%8s", agent_id);
				printf("Enter Agent Name: ");
				scanf("%32s", name);
				printf("Enter Agent Contact Info: ");
				scanf("%32s", contact_info);

				char insert_query[256];
				sprintf(insert_query, "INSERT INTO Agent (AgentID, Name, ContactInfo) VALUES ('%s', '%s', '%s')", agent_id, name, contact_info);

				state = mysql_query(connection, insert_query);
				if (state == 0) {
					printf("New agent added successfully.\n");

					// Commit the transaction
					if (mysql_commit(connection) == 0) {
						printf("Transaction committed successfully.\n");

						// Print all agents
						printf("\n---- All Agents ----\n");
						char all_agents_query[] = "SELECT * FROM Agent";
						state = mysql_query(connection, all_agents_query);
						if (state == 0) {
							sql_result = mysql_store_result(connection);
							printf("AgentID\t\tName\t\tContactInfo\n");
							while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
								printf("%-10s %-20s %-20s\n", sql_row[0], sql_row[1], sql_row[2]);
							}
							mysql_free_result(sql_result);
						}
						else {
							printf("Failed to retrieve agents: %s\n", mysql_error(connection));
						}
					}
					else {
						printf("Failed to commit transaction: %s\n", mysql_error(connection));
					}
				}
				else {
					printf("Failed to add new agent: %s\n", mysql_error(connection));
				}
			}
			else if (type_num == 0) {
				main_flag = true;
				continue;
			}

			else {
				printf("You Typed wrong number \n");
				continue;
			}
		}
		while (fgets(buffer, sizeof(buffer), fp) != NULL)
			mysql_query(connection, buffer);			// these are DELETEs & DROPs.

		mysql_close(connection);
	}

	mysql_close(connection);
	return 0;
}
