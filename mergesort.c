void MergeSortChar(node ** headPtrPtr) 
{ 
  node* head = *headPtrPtr; 
  node* nodePtrOne; 
  node* nodePtrTwo; 

  //length is 0 or 1
  if ((head == NULL) || (head->next == NULL)) 
  { 
    return; 
  }
 
  
  //split into sublists
  splitIntoSublists(head, &nodePtrOne, &nodePtrTwo);  
  
  //sort the sublists
  MergeSortChar(&nodePtrOne); 
  MergeSortChar(&nodePtrTwo); 


  //merge sorted sublist
  *headPtrPtr = SortedMergeChar(nodePtrOne, nodePtrTwo); 
}

node* SortedMergeInt(node* nodePtrOne, node* nodePtrTwo) 
{ 
  node* result = NULL; 
  
  //check if nodes are null
  if (nodePtrOne == NULL) 
    return(nodePtrTwo); 
  else if (nodePtrTwo==NULL) 
    return(nodePtrOne); 

  //if(dataType == 0) //Sort on chars
  //{

  //choose where to recur
  if (nodePtrOne->intValue < nodePtrTwo->intValue) 
  {  
    result = nodePtrOne; 
    result->next = SortedMergeInt(nodePtrOne->next, nodePtrTwo); 
  } 
  else
  { 
    result = nodePtrTwo; 
    result->next = SortedMergeInt(nodePtrOne, nodePtrTwo->next); 
  } 
  //}
  /*
  else if(dataType == 1) //Sort on ints
  {
  
    if (a->intValue <= b->intValue) 
    { 
      result = a; 
      result->next = SortedMergeChar(a->next, b, dataType); 
    } 
    else
    { 
      result = b; 
      result->next = SortedMergeChar(a, b->next, dataType); 
    } 
  }
  */
  return(result); 
}

node* SortedMergeFloat(node* nodePtrOne, node* nodePtrTwo) 
{ 
  node* result = NULL; 
  
  //check if nodes are null
  if (nodePtrOne == NULL) 
    return(nodePtrTwo); 
  else if (nodePtrTwo==NULL) 
    return(nodePtrOne); 

  //if(dataType == 0) //Sort on chars
  //{

  //choose where to recur
  if (nodePtrOne->floatValue <= nodePtrTwo->floatValue) 
  {  
    result = nodePtrOne; 
    result->next = SortedMergeFloat(nodePtrOne->next, nodePtrTwo); 
  } 
  else
  { 
    result = nodePtrTwo; 
    result->next = SortedMergeFloat(nodePtrOne, nodePtrTwo->next); 
  } 
  //}
  /*
  else if(dataType == 1) //Sort on ints
  {
  
    if (a->intValue <= b->intValue) 
    { 
      result = a; 
      result->next = SortedMergeChar(a->next, b, dataType); 
    } 
    else
    { 
      result = b; 
      result->next = SortedMergeChar(a, b->next, dataType); 
    } 
  }
  */
  return(result); 
}

void MergeSortInt(node ** headPtrPtr) 
{ 
  node* head = *headPtrPtr; 
  node* nodePtrOne; 
  node* nodePtrTwo; 

  //length is 0 or 1
  if ((head == NULL) || (head->next == NULL)) 
  { 
    return;
  }
 
  
  //split into sublists
  splitIntoSublists(head, &nodePtrOne, &nodePtrTwo);  
  
  //sort the sublists
  MergeSortInt(&nodePtrOne);
  MergeSortInt(&nodePtrTwo);


  //merge sorted sublist
  *headPtrPtr = SortedMergeInt(nodePtrOne, nodePtrTwo); 
} 

void MergeSortFloat(node ** headPtrPtr) 
{ 
  node* head = *headPtrPtr; 
  node* nodePtrOne; 
  node* nodePtrTwo; 

  //length is 0 or 1
  if ((head == NULL) || (head->next == NULL)) 
  { 
    return;
  }
 
  
  //split into sublists
  splitIntoSublists(head, &nodePtrOne, &nodePtrTwo);  
  
  //sort the sublists
  MergeSortFloat(&nodePtrOne);
  MergeSortFloat(&nodePtrTwo);


  //merge sorted sublist
  *headPtrPtr = SortedMergeFloat(nodePtrOne, nodePtrTwo); 
} 

node* SortedMergeChar(node* nodePtrOne, node* nodePtrTwo) 
{ 
  node* result = NULL; 
  
  //check if nodes are null
  if (nodePtrOne == NULL) 
    return(nodePtrTwo); 
  else if (nodePtrTwo==NULL) 
    return(nodePtrOne); 

  //if(dataType == 0) //Sort on chars
  //{
  //choose how to recur
  if (strcmp(nodePtrOne->charValue, nodePtrTwo->charValue) < 0) 
  {  
    result = nodePtrOne; 
    result->next = SortedMergeChar(nodePtrOne->next, nodePtrTwo); 
  } 
  else
  { 
    result = nodePtrTwo; 
    result->next = SortedMergeChar(nodePtrOne, nodePtrTwo->next); 
  } 
  //}
  /*
  else if(dataType == 1) //Sort on ints
  {
  
    if (a->intValue <= b->intValue) 
    { 
      result = a; 
      result->next = SortedMergeChar(a->next, b, dataType); 
    } 
    else
    { 
      result = b; 
      result->next = SortedMergeChar(a, b->next, dataType); 
    } 
  }
  */
  return(result); 
}

  
//splits into sublists
void splitIntoSublists(node* sourcePtr, node** frontPtrPtr, node** backPtrPtr) 
{ 
  node* fast; 
  node* slow; 
  slow = sourcePtr; 
  fast = sourcePtr->next; 
  
  /* Advance 'fast' two nodes, and advance 'slow' one node */
  while (fast != NULL) 
  { 
    fast = fast->next; 
    if (fast != NULL) 
    { 
        slow = slow->next; 
        fast = fast->next; 
    } 
  } 
  
  ///slow before midpoint so split into sublists here
  *frontPtrPtr = sourcePtr; 
  *backPtrPtr = slow->next; 
  slow->next = NULL; 
} 