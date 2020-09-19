# Point-of-Sale
Socket Programming to implement a simple cliient and server that communicate over the network and implementation of Cash Registers that
has a "**Concurrent Server**". The client supplies a sequence of codes corresponding to some product and the server returns the price of each,and if the product is available, while keeping a track of total cost of the purchases of the client

This was done as a course project in our Networks Lab by
Aditya Raj,Parv Sood and Sahilpreet Singh Thind

### request message format
  | **Request_Type** | **UPC-Code** | **Number** |
  |------------------|--------------|------------|  

The format of the request message where:

**Request_Type** is either 0 for item or 1 for close

**UPC-Code** is a 3-digit code for the product

**Number** gives quantity of the product requested
for the **Close** command the server returns the total cost of the items requested

### response message format
  |**Response_Type**|**Response**|
  |-----------------|------------|
  
**Response_Type** is 0 for OK and 1 for error

**Response** returns the total amount on 'close', {price ,name} for item and error message for error
