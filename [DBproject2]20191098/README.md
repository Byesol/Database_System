# Project Name

## 개요

이 프로젝트는 MySQL 데이터베이스에 연결하여 다양한 쿼리를 수행하는 프로그램입니다. 프로그램은 사용자로부터 입력을 받아 주어진 SQL 쿼리를 실행하고, 결과를 출력합니다. 주요 기능으로는 특정 지역의 부동산 정보 조회, 거래 내역 분석, 그리고 새로운 에이전트 추가 등이 포함됩니다.

## 환경 설정

### 필수 소프트웨어

- **MySQL**: 데이터베이스 서버
- **libmysql**: MySQL 클라이언트 라이브러리
- **C/C++ 컴파일러**: GCC, Clang 등

### 라이브러리 링크

```cpp
#pragma comment(lib, "libmysql.lib")
```

### 프로젝트 설정

프로젝트를 설정하려면 다음 라이브러리를 설치해야 합니다.

- Windows의 경우, MySQL Connector/C++를 설치하여 `libmysql.lib`를 포함시켜야 합니다.

## 설치 및 실행

### MySQL 데이터베이스 설정

host = "localhost";
user = "root";
pw = "직접입력";

### 실행 환경 - Visual Studio

프로젝트 내에 2019109.txt (CRUD 파일) 요구됨
프로젝트의 디렉토리를 MYSQL과 연결

## 사용법

프로그램 실행 후, 다음과 같은 메뉴가 표시됩니다.

```
-------- SELECT QUERY TYPES --------

    1. TYPE 1
    2. TYPE 2
    3. TYPE 3
    4. TYPE 4
    5. TYPE 5
    6. TYPE 6
    7. TYPE 7
    0. QUIT
Type number of which number Type:
```

각 기능에 대한 설명은 아래와 같습니다.

- **TYPE 1**: (TYPE1) Find address of homes for sale in the district “Mapo”. (1) (TYPE 1-1) Then find the costing between ￦ 1,000,000,000 and ￦ 1,500,000,000
- **TYPE 2**: Find the address of homes for sale in the 8th school distric (TYPE 2-1) Then find properties with 4 or more bedrooms and 2 bathrooms
- **TYPE 3**: Find the name of the agent who has sold the most properties in the year 2022 by total won value (TYPE 3-1) Then find the top k agents in the year 2023 by total won value (TYPE 3-2) And then find the bottom 10% agents in the year 2021 by total won value
- **TYPE 4**: For each agent, compute the average selling price of properties sold in 2022, and the average time the property was on the market. (TYPE 4-1) Then compute the maximum selling price of properties sold in 2023 for each agent. (9) - (TYPE 4-2) And then compute the longest time the property was on the market for each agent.
- **TYPE 5**: (TYPE 5) Show photos of the most expensive studio, one-bedroom, multi-bedroom apartment(s), and detached house(s), respectively, from the database
- **TYPE 6**: (TYPE 6) Record the sale of a property that had been listed as being available. This entails storing the sales price, the buyer, the selling agent, the buyer’s agent(if
  any), and the date
- **TYPE 7**: (TYPE 7) Add a new agent to the database.

## 사용법 - 절차

- 1. 먼저 인터페이스가 사용자에게 제시되고 사용자는제시된 8가지의 선택지 중 원하는 쿼리를 사용자는 숫자 하나를 입력합다. (0을 입력해 이전 단계 혹은, 프로그램 종료 가능)
- 2. 사용자가 입력한 쿼리의 명령이 실행돼고 해당 쿼리의 결과가 출력됩니다. 이 때 서브쿼리가 존재할 수 있습니다.
- 3. 서브쿼리가 존재한다면 마찬가지로 해당 번호를 입력해 해당 서브쿼리의 결과를 출력합니다.
- 4. 3-1, 6,7번 쿼리의 경우 사용자에게 입력값을 요구합니다. 3-1의 경우 상위 몇 개를 출력할지, 6번의 경우 판매중인 매물을 업데이트할 정보, 7번은 새로운 agent에 대한 정보를 입력해야 합니다.

## 사용법 - 주의사항

- 1. 6번 쿼리의 경우 BuyerID와 BuyerAgentID를 입력할 때 데이터에 존재하는 BuyerID와 BuyerAgentID를 입력해야 합니다. 그렇지 않다면 계속 다시 입력해야 합니다. agent는 A0000001부터 A0000005까지 현재 20191098.txt에 있으며 buyer의 경우 B0000001부터 B0000004까지 있습니다.

- 2. 6번 쿼리에서 DateSold를 입력할 때는 SaleDate보다 나중의 날짜를 입력해야 합니다.(제한조건)
- 3. 3-1에서 k값을 입력할 때 현재 agent는 10명 있으므로 10명을 넘게 입력해도 최대 10명만 출력됩니다.
- 4. 3-2에서 하위 10%의 수를 구할 때는 소수점은 제외하고 구합니다. ex 1.5명 -> 1명

### 예시 쿼리

- **TYPE 1-1**: 가격이 1,000,000,000원에서 1,500,000,000원 사이인 매물 주소 조회

```sql
SELECT Property.address FROM Property JOIN Transaction ON Property.PropertyID = Transaction.PropertyID WHERE Property.District = 'Mapo' AND Transaction.SalePrice IS NULL AND Transaction.ListingPrice BETWEEN 1000000000 AND 1500000000;
```

- **TYPE 3-1**: 2023년에 가장 많은 매물을 판매한 상위 k명의 에이전트 조회

```sql
SELECT Agent.Name FROM Agent JOIN (SELECT SellerAgentID, SUM(SalePrice) AS TotalSale FROM Transaction WHERE YEAR(SaleDate) = 2023 GROUP BY SellerAgentID ORDER BY TotalSale DESC LIMIT k) AS TopAgents ON Agent.AgentID = TopAgents.SellerAgentID;
```
