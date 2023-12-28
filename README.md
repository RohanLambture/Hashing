Problem: Special Phone Book Management

You are tasked with developing a specialised phone book management system that empowers users to save, find, and remove contact information efficiently. This innovative phone book allows users to store extensive details, encompassing names, organisations, and multiple phone numbers associated with each contact.

Features:

1. Adding Contacts:
   - Users can input comprehensive contact information, including individuals' names, their associated organisations, and one or more phone numbers.

2. Finding Contacts:
   - The system supports versatile contact searches based on people's names. Users can initiate searches using full names, partial names (first name, middle name, last name), or any combination thereof.

3. Removing Contacts:
   - Users can seamlessly delete contact information that is no longer needed. This removal process includes erasing details such as names, associated organisations, and phone numbers.

Classes:

1.ContactRecord` Class:
   - Represents an individual contact record with attributes `name`, `organisation`, and `phone numbers`.
   - Provides methods to retrieve individual attributes.

2. PhoneBookManager Class:
   - Orchestrates the overall functionality of the specialised phone book.
   - Utilizes efficient data structures for storing and retrieving contact records.

Key Functions:

1.add contact(const ContactRecord *record)
   - Incorporates a new contact into the specialised phone book system. The contact record comprises the person's name, organisation, and one or more phone numbers.

2.find contacts(const string *query) -> vector<ContactRecord >
   - Retrieves contacts based on a query string, offering flexibility in search options.

3.remove contact(const string *search name) -> bool
   - Deletes a contact from the phone book system based on the provided name. Returns `true` if the contact is successfully removed and `false` otherwise.

Constraints:

- The phone book should adeptly manage a large number of contacts.
- Implement practical search algorithms to cater to various search queries.
- Ensure proper memory management for dynamically allocated objects.

